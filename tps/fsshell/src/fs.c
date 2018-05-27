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

int img_open(char* nomearq) {
  int fd = -1;
  
  fd = open(nomearq, O_RDONLY);
  if (fd == -1) {
      perror("Falha ao abrir imagem.");
      return 0;
   } else {
     return 1;
   }
}

int sh_getcmd(char* nomeimg, char *buf, int nbuf) {
  /* Checa se o stdin é um terminal */
  if (isatty(fileno(stdin)))
    fprintf(stdout, "%s> ", nomeimg);
  memset(buf, 0, nbuf);
  fgets(buf, nbuf, stdin);
  if (buf[0] == 0) /* EOF (hora de ir embora, tchau) */
    return 0;
  return 1;
}

int main(int argc, char *argv[]) {
  static char buf[SHBUFFER];
  char* arquivoimagem;
 
  if (argc < 2) {
    fprintf(stdout, "Número de argumentos insuficientes.\n");
    exit(EXIT_FAILURE);
  }
  arquivoimagem = argv[1];
  if (!img_open(arquivoimagem)) {
    exit(EXIT_FAILURE);
  }
  while (sh_getcmd(arquivoimagem, buf, sizeof(buf))) {
    
  }
  exit(EXIT_SUCCESS);
}
