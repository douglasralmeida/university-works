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

void str_trim(char *str) {
  int i;
  int inicio = 0;
  int final = strlen(str) - 1;
  while (isspace((unsigned char) str[inicio]))
    inicio++;
  while ((final >= inicio) && isspace((unsigned char) str[final]))
    final--;

  /* Empurra todos os caracterse para o inicio da cadeia. */
  for (i = inicio; i <= final; i++)
    str[i - inicio] = str[i];
  str[i - inicio] = '\0';
}

void fs_init() {
  fs.imgdesc = -1;
  fs.pwd[0] = '/';
  fs.pwd[1] = '\0';
}

int img_open(char* nomearq) {
  fs.imgdesc = open(nomearq, O_RDONLY);
  if (fs.imgdesc == -1) {
      perror("Falha ao abrir imagem.");
      return 0;
   }
  fs.imgnome = nomearq;
    
  return 1;
}

void sh_init() {
  shcmds.functions = shcmds_func;
  shcmds.names = shcmds_name;
}

void sh_cmd_pwd() {
  fputs(fs.pwd, stdout);
}

int shcmds_lookup(char* cmd) {
  int i;
  
  for (i = SHCMDSMAX - 1; i >= 0; i--) {
    if (!strcmp(cmd, shcmds.names[i]))
      return i;
  }
  
  return i;
}

void shcmds_call(int index) {
  shcmds.functions[index]();
  fputc('\n', stdout);
}

int sh_getcmd(char *buf, int nbuf) {
  /* Checa se o stdin é um terminal */
  if (isatty(fileno(stdin)))
    fprintf(stdout, "%s> ", fs.imgnome);
  memset(buf, 0, nbuf);
  fgets(buf, nbuf, stdin);
  if (buf[0] == 0) /* EOF (hora de ir embora, tchau) */
    return 0;
  return 1;
}

void sh_run() {
  static char buf[SHBUFFER];
  int cmdindex;

  while (sh_getcmd(buf, sizeof(buf))) {
    str_trim(buf);
    /* comando exit */
    if (buf[0] == 'e' && buf[1] == 'x' && buf[2] == 'i' && buf[3] == 't' && buf[4] == '\0')
      return;
      
    cmdindex = shcmds_lookup(buf);
    if (cmdindex >= 0)
      shcmds_call(cmdindex);
  }
}

int main(int argc, char *argv[]) { 
  if (argc < 2) {
    fprintf(stdout, "A sintaxe do comando está incorreta.\n");
    exit(EXIT_FAILURE);
  }
  fs_init();
  sh_init();
  if (!img_open(argv[1])) {
    exit(EXIT_FAILURE);
  }
  sh_run();
  exit(EXIT_SUCCESS);
}
