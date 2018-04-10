//ALUNO Saulo Weikert Bicalho
//ALUNO Douglas Rodrigues de Almeida

#include <dirent.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>

#define MAXPROCS 20

/* ------   TAD USUARIOS   ------ */
typedef struct {
  char nome[33]; //No Linux usernames tem no maximo 32 caracteres (man useradd)
  int uid;
} usuario;

/* ------   TAD USUARIOS   ------ */
typedef struct {
  usuario lista_usuario[1024];
  int quantidade;
} usuarios;

char* usuarios_nomeporid(usuarios* us, int id) {
  int i;
  
  for (i = 0; i < us->quantidade; i++) {
    if (us->lista_usuario[i].uid == id)
      return us->lista_usuario[i].nome;
  }
  return NULL;
}

/* obter a lista de usuarios (id, nome) do sistema */
void usuarios_obter(usuarios* us) {
  int i = 0;

  FILE *file;
  const char del[2] = ":";
  char temp[256];
  char* p;

  file = fopen("/etc/passwd","rt");
  if (!file) {
    printf("Erro ao acessar /etc/passwd.\n");
    exit(EXIT_FAILURE);
  }

  while (fgets(temp, sizeof(temp), file) && i < 1024) {
    p = strtok(temp, del);
    strcpy(us->lista_usuario[i].nome, p); 
    strtok(NULL, del);
    us->lista_usuario[i].uid = atoi(strtok(NULL, del));
    i++;
  }
  us->quantidade = i;
  fclose(file);
}

/* ------   TAD PROCESSO   ------ */
typedef struct {
  int id;
  char nome[17]; //No Linux processnames tem no maximo 16 caracteres
  char estado;
  int usuario;
} processo;

/* obtem informações de cada processo */
void processo_obter(processo* proc) {
  FILE* fd;
  char nomearquivo[32];

  sprintf(nomearquivo, "/proc/%d/status", proc->id);
  fd = fopen(nomearquivo, "rt");
  if (!fd) {
    printf("Erro ao acessar /proc/%d/status.\n", proc->id);
    exit(EXIT_FAILURE);
  }
  
  fscanf(fd, "%*s %s", proc->nome);
  fscanf(fd, "%*s %*s %c %*s", &proc->estado);
  fscanf(fd, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d", &proc->usuario);
  fclose(fd);
}

/* ------   TAD PROCESSOS   ----- */
typedef struct {
  processo lista[20];
  int tamanho;
} processos;

/* obtem a lista de processos do sistema */
void processos_obter(processos* procs) {
  int i = 0;
  DIR *dir;
  struct dirent *de;

  dir = opendir("/proc");
  if (!dir) {
    printf("Erro ao acessar /proc.\n");
    exit(EXIT_FAILURE);
  }
  readdir(dir);
  readdir(dir);
  
  while (((de = readdir(dir)) != NULL) && i < MAXPROCS) {
    if ((de->d_type == DT_DIR) && (isdigit(de->d_name[0]))) {
      procs->lista[i].id = atoi(de->d_name);
      processo_obter(procs->lista + i);
      i++;
    }
  }
  procs->tamanho = i;
  closedir(dir);
}

/* limpa a tela (numlinhas anteriores ao cursor para limpar) */
void processos_exibir_limpartela(int numlinhas) {
  int i;
 
  for (i = 0; i < numlinhas+1; i++) {
    printf("\033[A");
  }
  printf("\33[2K");
}

void processos_exibir_cabeca() {
  printf("\r   PID| Usuario                  | PROCNOME           | Estado |\n");
  printf("------|--------------------------|--------------------|--------|\n");
}

void processos_exibir_corpo(processos* procs, usuarios* us) {
  int i;
  char* usuarionome;
  
  for (i = 0; i < procs->tamanho; i++) {
    usuarionome = usuarios_nomeporid(us, procs->lista[i].usuario);
    if (!usuarionome)
      usuarionome = "<nãoencont>";
    printf("\r%6d|%26s|%20s| %c      |\n", procs->lista[i].id, usuarionome, procs->lista[i].nome, procs->lista[i].estado);
  }
}

void processos_exibir_rodape() {
  printf("Pressione ENTER para parar a atualização.\n");
}

/* ---   THREAD PROCESSOS   ---- */
void* processar() {
  processos procs;
  usuarios us;

  usuarios_obter(&us);
  processos_obter(&procs);
  processos_exibir_cabeca();
  processos_exibir_corpo(&procs, &us);
  processos_exibir_rodape();
  sleep(1);
  do {
    processos_exibir_limpartela(MAXPROCS);
    usuarios_obter(&us);
    processos_obter(&procs);
    processos_exibir_corpo(&procs, &us);
    processos_exibir_rodape();
    sleep(1);
  } while (1);
  
  pthread_exit(EXIT_SUCCESS);
}

/* --------   SHELL   --------- */
int getcmd(char *buf, int nbuf) {
  if (isatty(fileno(stdin)))
    fprintf(stdout, "> ");
  memset(buf, 0, nbuf);
  fgets(buf, nbuf, stdin);
  if(buf[0] == 0) // EOF
    return -1;
  return 0;
}

/* -------   SINAIS   --------- */
void envia_sinal(int pid, int sinal) {
  if (kill(pid, sinal) < 0)
    perror("Erro ao enviar sinal");
}

/* --------   MAIN   ---------- */
int main() {
  static char buf[100];
  int pid;
  int sinal;
 
  pthread_t thread;
  pthread_attr_t attr;

  pthread_attr_init(&attr);
  pthread_create(&thread, &attr, processar, NULL);
  getchar();//Quando o usuario pressionar ENTER, mata a thread e exibe o shell
  fflush(stdin);
  pthread_cancel(thread);
  pthread_join(thread, NULL);
  while(getcmd(buf, sizeof(buf)) >= 0) { //Shell para enviar sinais para outros processos (pid signal) ou q para sair
    if (buf[0] == 'q' && buf[1] == '\n') {
      break;
    }
    
    if (sscanf(buf, "%d %d", &pid, &sinal) != 2) {
      printf("Comando desconhecido.\n");
      continue;
    }
    envia_sinal(pid, sinal);
  }

  return EXIT_SUCCESS;
}
