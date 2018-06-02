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

void str_trim(char *str) {
  int i;
  int inicio = 0;
  int final = strlen(str) - 1;
  while (isspace((unsigned char) str[inicio]))
    inicio++;
  while ((final >= inicio) && isspace((unsigned char) str[final]))
    final--;

  /* Empurra todos os caracteres para o inicio da cadeia. */
  for (i = inicio; i <= final; i++)
    str[i - inicio] = str[i];
  str[i - inicio] = '\0';
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
  fs.block_size = BLOCK_SIZE(fs.super_block->log_block_size);
  
  /* checa o número mágico do ext2 */
  if (fs.super_block->magic != EXT2_SUPER_MAGIC) {
    munmap(fs.ptr, fs.size);
    close(fs.imgdesc);
    fprintf(stderr, "Arquivo de imagem inválido. Formato irreconhecível\n");
    return 0;
  }

  return 1;
}

/****    SHELL    ****/

/* comandos do shell */
void sh_cmd_info() {
  fprintf(stdout, "Nome do arquivo de imagem:  %s\n", fs.imgname);
  fprintf(stdout, "Tamanho padrão de um bloco: %u KB", fs.block_size / 1024);
}

void sh_cmd_pwd() {
  fputs(fs.pwd, stdout);
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
}

void sh_parse(char* line) {
  int i = 0;
  
  while (line[i] != '\0') {
    if (i == SHCMDBUFFER)
      break;
    if (isspace((unsigned char) line[i]))
      break;
    else
      usercmd.cmd[i] = line[i];
    i++;
  }
  usercmd.cmd[i] = '\0';
  while (isspace((unsigned char) line[i])) {
    i++;
  }
  usercmd.arg = line + i;
}

void sh_run() {
  static char buf[SHBUFFER];
  int cmdindex;

  while (sh_getcmd(buf, sizeof(buf))) {
    str_trim(buf);
    if (buf[0] == '\0')
      continue;

    /* comando exit */
    if (buf[0] == 'e' && buf[1] == 'x' && buf[2] == 'i' && buf[3] == 't' && buf[4] == '\0') {
      fflush (stdout);
      return;  
    }
    sh_parse(buf);
    cmdindex = shcmds_lookup(usercmd.cmd);
    if (cmdindex >= 0)
      shcmds_call(cmdindex);
    else
      fprintf(stderr, "'%s' não foi reconhecido como um comando válido.\n", usercmd.cmd);
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
