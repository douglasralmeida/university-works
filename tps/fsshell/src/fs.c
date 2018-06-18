/*
**	TP3 de SO
**	A1
**  A2
**
*/

#include "ctype.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "unistd.h"
#include "fcntl.h"
#include "fs.h"
#include "sys/mman.h"
#include "sys/stat.h"

/****    STRING UTILS    ****/

int str_split(char* line, char* dels, char** array, int max) {
  int i = 0;
  char* token;
  
  token = strtok(line, dels);
  while (token != NULL && i < max) {
    array[i] = token;
    i++;
    token = strtok(NULL, dels);
  } 
  array[i] = NULL;
  
  return i;
}

void str_trim(char *str) {
  int i;
  int inicio = 0;
  int final;
  
  while (isspace((unsigned char) str[inicio]))
    inicio++;
  final = strlen(str) - 1;
  while ((final >= inicio) && isspace((unsigned char) str[final]))
    final--;

  /* Empurra todos os caracteres para o inicio da cadeia. */
  for (i = inicio; i <= final; i++)
    str[i - inicio] = str[i];
  str[i - inicio] = '\0';
}

/***   EXT2   ***/

/* caminha x bytes pela imagem */
void* ext2_lseek(const uint32 numbytes) {
  return (void*)((char*)fs.super_block + numbytes - BOOT_OFFSET);
}

/* obtem a posição do bloco */
void* ext2_getblock(const uint32 numblock) {
  return ext2_lseek(numblock * fs.block_size);
}

/* checa o nome da entrada de diretório */
char* ext2_dirent_getname(ext2_dir_entry* entry) {
  return (char*)entry + EXT2_NAME_OFFSET;
}

/* checa o nome da entrada de diretório */
int ext2_dirent_comparename(ext2_dir_entry* entry, char* name) { 
  char* entryname;

  entryname = ext2_dirent_getname(entry);
  return (name[(int)entry->name_len] == '\0' && !strncmp(name, entryname, entry->name_len));
}

ext2_group_desc* ext2_getgroupdesc(const uint32 inode) {
  uint32 offset;
  uint32 blockgroup;
  uint32 block;
  
  blockgroup = (inode - 1) / fs.super_block->inodes_per_group;
  block = blockgroup * fs.super_block->blocks_per_group * fs.block_size;
  offset = block + sizeof(ext2_super_block) + BOOT_OFFSET;
  
  return (ext2_group_desc*)ext2_lseek(offset);
}

ext2_inode* ext2_getinode(const uint32 inode) {
  ext2_group_desc* gd = 0;
  unsigned int index = 0;
  void* table = 0;
  void* block = 0;

  /* índice do nó i na tabela de nós i */
  index = (inode - 1) % fs.super_block->inodes_per_group;
  
  /* descritores de grupo referente                  *
   * ao grupo de blocos onde o nó i pertence         */
  gd = ext2_getgroupdesc(inode);
  
  /* tabela de nós i que armazena o nó i */
  table = ext2_getblock(gd->inode_table);
  
  /* nó i */
  block = (char*)table + index * fs.super_block->inode_size;
  
  return  (ext2_inode*)block;
}

ext2_dir_entry* ext2_getdirentries(ext2_inode* inode, const uint32 block) {
  ext2_dir_entry* d;
  
  d = (ext2_dir_entry*)ext2_getblock(inode->block[block]);
  
  return d;
}

/****    FS    ****/

void fs_init() {
  fs.imgdesc = -1;
  fs.pwd[0] = '/';
  fs.pwd[1] = '\0';
}

void fs_exit() {
  munmap(fs.ptr, fs.size);
  close(fs.imgdesc);
}

/* retorna o nó i do arquivo, caso exista */
int fs_getinode_byname(ext2_dir_entry* entry, void* data) {
  inodeinfo_t* info;

  info = (inodeinfo_t*)data;
  if (ext2_dirent_comparename(entry, info->name)) {
    info->inode = entry->inode;
    return 1;
  } else {
    return 0;
  }  
}

void fs_finddir(ext2_inode* inode, char* path) {
  unsigned int i;
  int j;
  ext2_dir_entry* dir_entry = NULL;
  ext2_inode* newinode = NULL;
  uint32 blocks;
  uint32 maxlen;
  uint32 curlen = 0;
  char newpath[1024];
  char temppath[1024];
  char* itemname;

  strncpy(newpath, path, sizeof(newpath));
  strncat(newpath, "/", sizeof(newpath));
  blocks = inode->blocks / (fs.block_size / 512);
  maxlen = inode->size;
  for (i = 0; i < blocks && i < 12; i++) {
    curlen = 0;
    dir_entry = ext2_getdirentries(inode, i);
    while (dir_entry && dir_entry->name_len && curlen < maxlen) {
      itemname = ext2_dirent_getname(dir_entry);
      if (itemname[0] == '.' && dir_entry->name_len == 1) {
        dir_entry = (void*)((char*)dir_entry + dir_entry->rec_len);
        curlen += dir_entry->rec_len;
        continue;
      }
      if (itemname[0] == '.' && itemname[1] == '.' && dir_entry->name_len == 2) {
        dir_entry = (void*)((char*)dir_entry + dir_entry->rec_len);
        curlen += dir_entry->rec_len;
        continue;
      }
      temppath[0] = '\0';
      strncat(temppath, newpath, sizeof(temppath));
      j = strlen(temppath);      
      strncat(temppath, itemname, sizeof(temppath));
      temppath[j+dir_entry->name_len] = '\0';
      fprintf(stdout, "%s\n", temppath);
      newinode = ext2_getinode(dir_entry->inode);
      if (newinode->mode & IFDIR) {
        fs_finddir(newinode, temppath);
      }
 	    curlen += dir_entry->rec_len;
	    dir_entry = (void*)((char*)dir_entry + dir_entry->rec_len);
    }
  }
  /* TODO: ainda falta ler os dados indiretos do bloco 13, 14 e 15 */
}

int fs_interatedir(direntry_func_t action, ext2_inode* inode, void* data) {
  unsigned int i;
  ext2_dir_entry* dir_entry = NULL;
  uint32 blocks;
  uint32 maxlen;
  uint32 curlen = 0;
  
  blocks = inode->blocks / (fs.block_size / 512);
  maxlen = inode->size;
  for (i = 0; i < blocks && i < 12; i++) {
    curlen = 0;
    dir_entry = ext2_getdirentries(inode, i);
    while (dir_entry && dir_entry->name_len && curlen < maxlen) {
      if (action(dir_entry, data))
        return 1;
 	    curlen += dir_entry->rec_len;
	    dir_entry = (void*)((char*)dir_entry + dir_entry->rec_len);
    }
  }
  /* TODO: ainda falta ler os dados indiretos do bloco 13, 14 e 15 */
  
  return 0;
}

void fs_setcurrdir(const uint32 inode) {
  fs.curr_dir.data = ext2_getinode(inode);
  fs.curr_dir.inode = inode;
}

int fs_direntry_goto(ext2_dir_entry* entry, void* data) {
  char* dirname;
  cdinfo_t* info;
  ext2_inode* inode;
  
  info = (cdinfo_t*)data;
  dirname = ext2_dirent_getname(entry);
  inode = ext2_getinode(entry->inode);
  if (!strncmp(info->nextdir, dirname, entry->name_len) && info->nextdir[(int)entry->name_len] == '\0') {
    if (!(inode->mode & IFDIR)) {
      info->isnotdir = 1;
      fprintf(stderr, "%s não é um diretório.\n", info->nextdir);
      return 0;
    }
    info->inode_index = entry->inode;
    info->inode_data = inode;
    return 1;
  }
  return 0;
}

int fs_direntry_show(ext2_dir_entry* entry, void* data) {
  char* dirname;
  
  dirname = ext2_dirent_getname(entry);  
  fprintf(stdout, "%.*s\n", (char)entry->name_len, dirname);
  
  return 0;
  if (data) {}
}

/****    IMG LEITOR    ****/

int img_open(char* nomearq) {
  struct stat imgstat;
  
  /* abre o arquivo da imagem */
  fs.imgdesc = open(nomearq, O_RDONLY);
  if (fs.imgdesc == -1) {
    perror("Falha ao abrir imagem.");
    return 0;
  }
  fs.imgname = nomearq;
  
  /* lê metadados do arquivo da imagem */
  if (fstat (fs.imgdesc, &imgstat) == -1) {
    close(fs.imgdesc);
    perror("Falha ao ler informações da imagem.");
    return 0;
  }
  fs.size = imgstat.st_size;
  
  /* checa o tamanho do arquivo */
  if (fs.size == 0) {
    close(fs.imgdesc);
    fprintf(stderr, "Arquivo de imagem inválido. Tamanho de arquivo não pode ser nulo.\n");
    return 0;
  }
  
  /* mapeia o arquivo da imagem na memória */
  fs.ptr = mmap(NULL, fs.size, PROT_READ, MAP_PRIVATE, fs.imgdesc, 0);
  if (fs.ptr == MAP_FAILED) {
    close(fs.imgdesc);
    perror("Falha ao mapear arquivo da imagem na memória.");
    return 0;
  }
  
  /* carrega o primeiro superbloco */
  fs.super_block = (void*)((char*)fs.ptr + BOOT_OFFSET);
    
  /* checa o número mágico do ext2 */
  if (fs.super_block->magic != EXT2_SUPER_MAGIC) {
    munmap(fs.ptr, fs.size);
    close(fs.imgdesc);
    fprintf(stderr, "Arquivo de imagem inválido. Formato irreconhecível.\n");
    return 0;
  }
  
  /* carrega informações úteis */
  fs.block_size = BLOCK_SIZE(fs.super_block->log_block_size);

  return 1;
}

/****    SHELL    ****/

/****    funções dos comandos    ****/

void do_find(ext2_inode* inode) {
  char path[1024];
  
  path[0] = '.';
  path[1] = '\0';
  fprintf(stdout, "%s\n", path);
  fs_finddir(inode, path);
}

void do_stat_mode(uint32 mode, char* mask) {
  int i;
  
  for (i = 0; i < 9; i++)
    mask[i] = '-';
    
  if (mode & IRUSR)
    mask[0] = 'r';
  if (mode & IWUSR)
    mask[1] = 'w';
  if (mode & IXUSR)
    mask[2] = 'x';
    
  if (mode & IRGRP)
    mask[3] = 'r';
  if (mode & IWGRP)
    mask[4] = 'w';
  if (mode & IXGRP)
    mask[5] = 'x';
    
  if (mode & IROTH)
    mask[6] = 'r';
  if (mode & IWOTH)
    mask[7] = 'w';
  if (mode & IXOTH)
    mask[8] = 'x';
}

int do_stat_type(uint32 mode) {
  if (mode & IFIFO)
    return 0;
  if (mode & IFCHR)
    return 1;
  if (mode & IFDIR)
    return 2;
  if (mode & IFBLK)
    return 3;
  if (mode & IFREG)
    return 4;
  if (mode & IFLNK)
    return 5;
  if (mode & IFSOCK)
    return 6;
    
  return 7;
}

void do_stat(uint32 iinode, ext2_inode* inode, char* filename) {
  uint32 blocks;
  char* accessmask;
  char timestr[80];
  int filetype;
  struct tm* ts;
  time_t tt;
  
  accessmask = (char*)malloc(sizeof(char) * 9);  
  blocks = inode->blocks / (fs.block_size / 512);
  do_stat_mode(inode->mode, accessmask);
  filetype = do_stat_type(inode->mode);
  
  fprintf(stdout, "         Arquivo: '%s'\n", filename);
  fprintf(stdout, "            Tipo: '%s'\n", ext2_inode_type[filetype]);
  fprintf(stdout, "         Tamanho: %u         Blocos: %u             Bloco ES: %u\n", inode->size, blocks, fs.block_size);
  fprintf(stdout, "          Imagem: %.*s       Nó i: %u               Links: %u\n", 12, fs.imgname, iinode, inode->links_count);
  fprintf(stdout, "          Acesso: %.*s    Uid: %u                Gid: %u\n", 12, accessmask, inode->uid, inode->gid);
  
  tt = inode->atime;
  ts = localtime(&tt);
  strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", ts);
  fprintf(stdout, "     Ult. acesso: %s\n", timestr);
  
  tt = inode->mtime;
  ts = localtime(&tt);
  strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", ts);
  fprintf(stdout, "Ult. modificação: %s\n", timestr);

  tt = inode->ctime;
  ts = localtime(&tt);
  strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", ts);
  fprintf(stdout, "    Ult. criação: %s\n", timestr);
  
  free(accessmask);
}

/* comandos do shell */
void sh_cmd_info() {
  fprintf(stdout, "Nome do arquivo de imagem:  %s\n", fs.imgname);
  fprintf(stdout, "Tamanho de um bloco: %u KB\n", fs.block_size / 1024); 
  fprintf(stdout, "Tamanho de um nó i:         %u bytes\n", fs.super_block->inode_size);
  fprintf(stdout, "Quant. de nós i por grupo:  %u\n", fs.super_block->inodes_per_group);
}

void sh_cmd_cd(void) {
  char* c;
  int startroot = 0;
  int subdircount = 0;
  int subdirpos = 0;
  int pwdcharzeropos;
  char* path[CD_PATH_MAX];
  cdinfo_t info;
  
  if (usercmd.argc < 2) {
    fprintf(stderr, "A sintaxe do comando está incorreta.\n");
    return;
  }
  pwdcharzeropos = strlen(fs.pwd);
  startroot = (usercmd.argv[1][0] == '/');
  if (startroot && fs.curr_dir.inode != EXT2_ROOT_INO) {
    info.inode_data = ext2_getinode(EXT2_ROOT_INO);
    info.inode_index = EXT2_ROOT_INO;
  } else {
    info.inode_data = fs.curr_dir.data;
    info.inode_index = fs.curr_dir.inode;
  }
  subdircount = str_split(usercmd.argv[1], "/", path, CD_PATH_MAX);
  if (!subdircount && fs.curr_dir.inode != EXT2_ROOT_INO) {
    fs.curr_dir.data = info.inode_data;
    fs.curr_dir.inode = info.inode_index;
    return;
  }
  info.nextdir = path[subdirpos];
  info.isnotdir = 0;
  while (fs_interatedir(&fs_direntry_goto, info.inode_data, (void*)(&info))) {
    subdirpos++;
    if (!strcmp(info.nextdir, "..")) {
      if (pwdcharzeropos > 1) {
        c = fs.pwd + pwdcharzeropos - 1;
        do {
          c--;
        } while (*c != '/');
        *(c+1) = '\0';
      }
    } else if (strcmp(info.nextdir, ".")) {
      strcat(fs.pwd, info.nextdir);
      strcat(fs.pwd, "/");    
    }
    if (subdirpos < subdircount)
      info.nextdir = path[subdirpos];
    else
      break;
  }
  if (subdirpos == subdircount) {
    fs.curr_dir.data = info.inode_data;
    fs.curr_dir.inode = info.inode_index;
  } else {
      fs.pwd[pwdcharzeropos] = '\0';
      if (!info.isnotdir)
        fprintf(stderr, "Arquivo ou diretório não encontrado.\n");
  }
}

void sh_cmd_exit(void) {
  usercmd.exiting = 1;
  fputs("Saindo...", stdout);
}

void sh_cmd_find(void) {
  ext2_inode* inode;
  uint32 iinode;

  if (usercmd.argc < 2) {
    inode = fs.curr_dir.data;
  } else {
    iinode = sh_getinode(usercmd.argv[1]);
    if (iinode) {
      inode = ext2_getinode(iinode);
    } else {
      fprintf(stderr, "Arquivo ou diretório não encontrado.\n");
      return;
    }
  }
  do_find(inode);
}

void sh_cmd_ls(void) {
  fs_interatedir(&fs_direntry_show, fs.curr_dir.data, NULL);
}

void sh_cmd_pwd() {
  fputs(fs.pwd, stdout);
}

void sh_cmd_sb(void) {
  int i;
  
  fputs("Dados do super bloco ext2\n", stdout);
  fputs("=========================\n", stdout);
  
  fprintf(stdout, "inodes_count = %u\n", fs.super_block->inodes_count);
  fprintf(stdout, "blocks_count = %u\n", fs.super_block->blocks_count);
  fprintf(stdout, "r_blocks_count = %u\n", fs.super_block->r_blocks_count);
  fprintf(stdout, "free_blocks_count = %u\n", fs.super_block->free_blocks_count);
  fprintf(stdout, "free_inodes_count = %u\n", fs.super_block->first_data_block);
  fprintf(stdout, "log_block_size = %u\n", fs.super_block->log_block_size);
  fprintf(stdout, "log_frag_size = %u\n", fs.super_block->log_frag_size);
  fprintf(stdout, "blocks_per_group = %u\n", fs.super_block->blocks_per_group);
  fprintf(stdout, "frags_per_group = %u\n", fs.super_block->frags_per_group);
  fprintf(stdout, "inodes_per_group = %u\n", fs.super_block->inodes_per_group);
  fprintf(stdout, "mtime = %u\n", fs.super_block->mtime);
  fprintf(stdout, "wtime = %u\n", fs.super_block->wtime);
  fprintf(stdout, "mnt_count = %u\n", fs.super_block->mnt_count);
  fprintf(stdout, "max_mnt_count = %u\n", fs.super_block->max_mnt_count);
  fprintf(stdout, "magic = %u\n", fs.super_block->magic);
  fprintf(stdout, "state = %u\n", fs.super_block->state);
  fprintf(stdout, "errors = %u\n", fs.super_block->errors);
  fprintf(stdout, "minor_rev_level = %u\n", fs.super_block->minor_rev_level);
  fprintf(stdout, "lastcheck = %u\n", fs.super_block->lastcheck);
  fprintf(stdout, "checkinterval = %u\n", fs.super_block->checkinterval);
  fprintf(stdout, "creator_os = %u\n", fs.super_block->creator_os);
  fprintf(stdout, "rev_level = %u\n", fs.super_block->rev_level);
  fprintf(stdout, "def_resuid = %u\n", fs.super_block->def_resuid);
  fprintf(stdout, "def_resgid = %u\n", fs.super_block->def_resgid);
  if (fs.super_block->rev_level == EXT2_DYNAMIC_REV) {
    fprintf(stdout, "first_ino = %u\n", fs.super_block->first_ino);
    fprintf(stdout, "inode_size = %u\n", fs.super_block->inode_size);
    fprintf(stdout, "block_group_nr = %u\n", fs.super_block->block_group_nr);
    fprintf(stdout, "rev_level = %u\n", fs.super_block->rev_level);
    fprintf(stdout, "feature_compat = %u\n", fs.super_block->feature_compat);
    fprintf(stdout, "feature_incompat = %u\n", fs.super_block->feature_incompat);
    fprintf(stdout, "feature_ro_compat = %u\n", fs.super_block->feature_ro_compat);
    fprintf(stdout, "uuid = ");
    for (i = 0; i < 16; i++)
      fprintf(stdout, "%u", fs.super_block->uuid[16]);
    fprintf(stdout, "\nvolume_name = %s\n", (char*)&fs.super_block->volume_name);
    fprintf(stdout, "last_mounted = %s\n", (char*)&fs.super_block->last_mounted);
    fprintf(stdout, "algorithm_usage_bitmap = %u\n", fs.super_block->algorithm_usage_bitmap);
    fprintf(stdout, "prealloc_blocks = %u\n", fs.super_block->prealloc_blocks);
    fprintf(stdout, "prealloc_dir_blocks = %u\n", fs.super_block->prealloc_dir_blocks);
    fprintf(stdout, "journal_uuid = ");
    for (i = 0; i < 16; i++)
      fprintf(stdout, "%u", fs.super_block->journal_uuid[i]);
    fprintf(stdout, "\njournal_inum = %u\n", fs.super_block->journal_inum);
    fprintf(stdout, "journal_dev = %u\n", fs.super_block->journal_inum);
    fprintf(stdout, "last_orphan = %u\n", fs.super_block->journal_inum);
    fprintf(stdout, "hash_seed = ");
    for (i = 0; i < 4; i++)
      fprintf(stdout, "%u", fs.super_block->hash_seed[i]);
    fprintf(stdout, "\ndef_hash_version = %u\n", fs.super_block->def_hash_version);
    fprintf(stdout, "default_mount_opts = %u\n", fs.super_block->default_mount_opts);
    fprintf(stdout, "first_meta_bg = %u\n", fs.super_block->first_meta_bg);
  }
}

void sh_cmd_stat(void) {
  ext2_inode* inode;
  uint32 iinode;

  if (usercmd.argc < 2) {
    fprintf(stderr, "A sintaxe do comando está incorreta.\n");
    return;
  }

  iinode = sh_getinode(usercmd.argv[1]);
  if (iinode) {
    inode = ext2_getinode(iinode);
    do_stat(iinode, inode, usercmd.argv[usercmd.argc-1]);
  } else {
    fprintf(stderr, "Arquivo ou diretório não encontrado.\n");
  }
}

void shcmds_call(int index) {
  shcmds.functions[index]();
  fputc('\n', stdout);
}

int shcmds_lookup(char* cmd) {
  int i;
  
  for (i = SHCMDSQUANT - 1; i >= 0; i--) {
    if (!strcmp(cmd, shcmds.names[i]))
      return i;
  }

  return i;
}

/* funções do shell */
int sh_getcmd(char *buf, int nbuf) {
  /* Checa se o stdin é um terminal */
  if (isatty(fileno(stdin)))
    fprintf(stdout, "%s> ", fs.imgname);
  memset(buf, 0, nbuf);
  fgets(buf, nbuf, stdin);
  if (buf[0] == 0) /* EOF (hora de ir embora, tchau) */
    return 0;
  return 1;
}

uint32 sh_getinode(char* path) {
  int startroot = 0;
  char* subdirs[CD_PATH_MAX];
  int subdircount = 0;
  int subdirpos = 0;
  inodeinfo_t data;
  ext2_inode* currentinode;

  /* começa da raiz ou do diretório atual? */
  startroot = (usercmd.argv[1][0] == '/');
  if (startroot) {
    currentinode = ext2_getinode(EXT2_ROOT_INO);
    data.inode = EXT2_ROOT_INO;
  } else {
    currentinode = fs.curr_dir.data;
    data.inode = fs.curr_dir.inode;
  }

  /* divide o caminho passado num vetor de subdiretórios */
  subdircount = str_split(path, "/", subdirs, CD_PATH_MAX);
  if (!subdircount)
    return data.inode;

  data.inode = 0;
  data.name = subdirs[subdirpos];
  
  /* navega pelo subdiretório atual */
  while (fs_interatedir(&fs_getinode_byname, currentinode, (void*)&data)) {
    /* encontrou uma entrada, tenta entrar */
    subdirpos++;
    if (subdirpos < subdircount) {
      currentinode = ext2_getinode(data.inode);
      if (!(currentinode->mode & IFDIR))
        return 0;
      data.name = subdirs[subdirpos];      
    }
    else
      break;
  }
  if (subdirpos == subdircount)
    return data.inode;
  else
    return 0;
}

void sh_init() {
  shcmds.functions = shcmds_func;
  shcmds.names = shcmds_name;
  usercmd.exiting = 0;
}

void sh_parse(char* line) {
  size_t len;
  
  len = strlen(line);
  if (line[len - 1] == '\n') {
    line[len -1] = '\0';
  }
  usercmd.argc = str_split(line, " ", usercmd.argv, ARG_MAX);
}

void sh_run() {
  static char buf[SHBUFFER];
  int cmdindex;
  
  /* começa com o diretório atual no diretório raiz */
  fs_setcurrdir(EXT2_ROOT_INO);

  /* espera por um comando da entrada */
  while (sh_getcmd(buf, sizeof(buf))) {
    sh_parse(buf);
    if (usercmd.argc > 0) {
      cmdindex = shcmds_lookup(usercmd.argv[0]);
      if (cmdindex >= 0)
        shcmds_call(cmdindex);
      else
        fprintf(stderr, "'%s' não foi reconhecido como um comando válido.\n", usercmd.argv[0]);
      if (usercmd.exiting) {
        fflush(stdout);
        return;
      }
    }
  }
}

/****    MAIN    ****/

int main(int argc, char *argv[]) { 
  if (argc < 2) {
    fprintf(stderr, "A sintaxe do comando está incorreta.\n");
    exit(EXIT_FAILURE);
  }
  fs_init();
  sh_init();
  if (!img_open(argv[1])) {
    exit(EXIT_FAILURE);
  }
  sh_run();
  fs_exit();
  exit(EXIT_SUCCESS);
}
