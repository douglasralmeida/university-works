/*
**	TP3 de SO
**	A1
**  A2
**
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "fs.h"

struct {
  char* imgnome;
  int   imgdesc;
} fs;

int img_open(char* nomearq) {
  fs.imgdesc = -1;
  fs.imgdesc = open(nomearq, O_RDONLY);
  if (fs.imgdesc == -1) {
      perror("Falha ao abrir imagem.");
      return 0;
   }
  fs.imgnome = nomearq;
    
  return 1;
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

  while (sh_getcmd(buf, sizeof(buf))) {
    
  }
}

int main(int argc, char *argv[]) { 
  if (argc < 2) {
    fprintf(stdout, "A sintaxe do comando está incorreta.\n");
    exit(EXIT_FAILURE);
  }
  if (!img_open(arqv[1])) {
    exit(EXIT_FAILURE);
  }
  sh_run();
  exit(EXIT_SUCCESS);
}
