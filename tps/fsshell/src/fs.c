/*
**	TP3 de SO
**	A1
**  A2
**
*/

#include "ctype.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
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

char* ext2_getdirname(ext2_dir_entry* entry) {
  return (char*)entry + EXT2_NAME_OFFSET;
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
    dir_entry = ext2_getdirentries(fs.curr_dir.data, i);
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
  dirname = ext2_getdirname(entry);
  inode = ext2_getinode(entry->inode);
  if (!strncmp(info->nextdir, dirname, entry->name_len) && info->nextdir[(int)entry->name_len] == '\0') {
    if (!(inode->mode & S_IFDIR)) {
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
  
  dirname = ext2_getdirname(entry);
  printf("%s\n", dirname);
  
  return 0;
  if (data) {
  }
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
  fputs("Comando 'find' ainda não implementado.", stdout);
}

void sh_cmd_ls(void) {
  fs_interatedir(&fs_direntry_show, fs.curr_dir.data, NULL);
}

void sh_cmd_pwd() {
  fputs(fs.pwd, stdout);
}

void sh_cmd_sb(void) {
  fputs("Comando 'sb' ainda não implementado.", stdout);
}

void sh_cmd_stat(void) {
  fputs("Comando 'stat' ainda não implementado.", stdout);
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
