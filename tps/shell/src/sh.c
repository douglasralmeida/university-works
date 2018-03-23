#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/* MARK NAME Douglas Rodrigues de Almeida */

/****************************************************************
 * Shell xv6 simplificado
 *
 * Este codigo foi adaptado do codigo do UNIX xv6 e do material do
 * curso de sistemas operacionais do MIT (6.828).
 ***************************************************************/

/* Quantidade maxima de argumentos do comando para execução */
#define MAXARGS 10
/* Buffer da linha de comando */
#define MAXBUFF 100

/* Todos comandos tem um tipo.  Depois de olhar para o tipo do
 * comando, o código converte um *cmd para o tipo específico de
 * comando. */
struct cmd {
  int type; /* ' ' (exec) ou
               '|' (pipe) ou
               '<' ou '>' (redirection) */
};

/* Comando para execução de um aplicativo */
struct execcmd {
  int type;              // ' '
  char *argv[MAXARGS];   // argumentos do comando a ser executado
};

/* Comando para execução de um aplicativo onde a entrada ou a saída
 * são arquivos */
struct redircmd {
  int type;          // < ou >
  struct cmd *cmd;   // o comando a rodar (ex.: um execcmd)
  char *file;        // o arquivo de entrada ou saída
  int mode;          // o modo no qual o arquivo deve ser aberto
  int fd;            // o número de descritor de arquivo que deve ser usado
};

/* Comando para execução de um aplicativo onde a entrada ou a saída
 * são a entrada ou a saída de outro comando para execução */
struct pipecmd {
  int type;          // |
  struct cmd *left;  // lado esquerdo do pipe
  struct cmd *right; // lado direito do pipe
};

// Função para fork do processo (fechar se ocorrer erro)
int fork1(void);

// Função para processar a linha de comando
struct cmd *parsecmd(char*);

/* Função para executar comando cmd. Nunca retorna. */
void runcmd(struct cmd *cmd) {
  struct execcmd* ecmd;
  struct pipecmd* pcmd;
  struct redircmd* rcmd;

  if (cmd == 0)
    exit(0);
  
  switch (cmd->type) {
    default:
      fprintf(stderr, "tipo de comando desconhecido\n");
      exit(-1);

    case ' ':
      ecmd = (struct execcmd*)cmd;
      if (ecmd->argv[0] == 0)
        exit(0);
   
      /* MARK START task2
       * TAREFA2: Implemente codigo abaixo para executar
       * comandos simples. */
      fprintf(stderr, "exec nao implementado\n");
      /* MARK END task2 */
    break;

    case '>':
    case '<':
      rcmd = (struct redircmd*)cmd;
      /* MARK START task3
       * TAREFA3: Implemente codigo abaixo para executar
       * comando com redirecionamento. */
      fprintf(stderr, "redir nao implementado\n");
      /* MARK END task3 */
      runcmd(rcmd->cmd);
    break;

    case '|':
      pcmd = (struct pipecmd*)cmd;
      /* MARK START task4
       * TAREFA4: Implemente codigo abaixo para executar
       * comando com pipes. */
      fprintf(stderr, "pipe nao implementado\n");
      /* MARK END task4 */
    break;
  }   
  exit(0);
}

/* Função exibir o prompt, ler o input e armazená-lo no buffer. 
 * Retorna -1 para encerrar o shell. Retorna 0 para continuar */
int getcmd(char *buf, int nbuf) {
  //Checa se o stdin é um terminal
  if (isatty(fileno(stdin)))
    fprintf(stdout, "$ ");
  memset(buf, 0, nbuf);
  fgets(buf, nbuf, stdin);
  if (buf[0] == 0) // EOF (hora de ir embora, tchau)
    return -1;
  return 0;
}

/****************************************************************
 * Funcao Main
 ***************************************************************/
int main(void) {
  static char buf[MAXBUFF];
  int r;

  // Ler input e rodar comandos
  while (getcmd(buf, sizeof(buf)) >= 0) {
    /* MARK START task1 */
    /* TAREFA1: O que faz o if abaixo e por que ele é necessário?
     * Insira sua resposta no código e modifique o fprintf abaixo
     * para reportar o erro corretamente. */
     
    /* Comando cd
     * Altera o diretório de trabalho */
    if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ') {
      buf[strlen(buf)-1] = 0;
      if (chdir(buf+3) < 0)
        fprintf(stderr, "reporte erro\n");
      continue;
    }
    /* MARK END task1 */

    /* Cria um processo e executa o aplicativo */
    if (fork1() == 0)
      runcmd(parsecmd(buf));
    wait(&r);
  }
  exit(0);
}

/* Faz a chamada de sistema fork() para criar um novo processo filho. */
int fork1(void) {
  int pid; //identificador do processo
  
  pid = fork();
  /* pid será -1 quando ocorrer um erro.
  	 pid será 0 quando estiver dentro do processo filho.
     pid sera >0 quando estiver dentro do processo pai. */
  if (pid == -1)
    perror("Erro do sistema operacional ao criar o processo.");
  return pid;
}

/****************************************************************
 * Funcoes auxiliares para criar estruturas de comando
 ***************************************************************/

// Função para alocar um execmd na memória
struct cmd* execcmd(void) {
  struct execcmd* cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = ' ';
  return (struct cmd*)cmd;
}

// Função para alocar um redircmd na memória
struct cmd* redircmd(struct cmd *subcmd, char *file, int type) {
  struct redircmd* cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = type;
  cmd->cmd = subcmd;
  cmd->file = file;
  cmd->mode = (type == '<') ?  O_RDONLY : O_WRONLY|O_CREAT|O_TRUNC;
  cmd->fd = (type == '<') ? 0 : 1;
  return (struct cmd*)cmd;
}

// Função para alocar um pipecmd na memória
struct cmd* pipecmd(struct cmd *left, struct cmd *right) {
  struct pipecmd *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = '|';
  cmd->left = left;
  cmd->right = right;
  return (struct cmd*)cmd;
}

/****************************************************************
 * Processamento da linha de comando
 ***************************************************************/

char whitespace[] = " \t\r\n\v";
char symbols[] = "<|>";

int gettoken(char **ps, char *es, char **q, char **eq) {
  char *s;
  int ret;
  
  s = *ps;
  while(s < es && strchr(whitespace, *s))
    s++;
  if(q)
    *q = s;
  ret = *s;
  switch(*s){
  case 0:
    break;
  case '|':
  case '<':
    s++;
    break;
  case '>':
    s++;
    break;
  default:
    ret = 'a';
    while(s < es && !strchr(whitespace, *s) && !strchr(symbols, *s))
      s++;
    break;
  }
  if(eq)
    *eq = s;
  
  while(s < es && strchr(whitespace, *s))
    s++;
  *ps = s;
  return ret;
}

int peek(char **ps, char *es, char *toks) {
  char *s;
  
  s = *ps;
  while(s < es && strchr(whitespace, *s))
    s++;
  *ps = s;
  return *s && strchr(toks, *s);
}

struct cmd *parseline(char**, char*);
struct cmd *parsepipe(char**, char*);
struct cmd *parseexec(char**, char*);

/* Copiar os caracteres no buffer de entrada, começando de s ate es.
 * Colocar terminador zero no final para obter um string valido. */
char *mkcopy(char *s, char *es) {
  int n = es - s;
  char *c = malloc(n+1);
  assert(c);
  strncpy(c, s, n);
  c[n] = 0;
  return c;
}

struct cmd* parsecmd(char *s) {
  char *es;
  struct cmd *cmd;

  es = s + strlen(s);
  cmd = parseline(&s, es);
  peek(&s, es, "");
  if(s != es){
    fprintf(stderr, "leftovers: %s\n", s);
    exit(-1);
  }
  return cmd;
}

struct cmd* parseline(char **ps, char *es) {
  struct cmd *cmd;
  cmd = parsepipe(ps, es);
  return cmd;
}

struct cmd* parsepipe(char **ps, char *es) {
  struct cmd *cmd;

  cmd = parseexec(ps, es);
  if (peek(ps, es, "|")) {
    gettoken(ps, es, 0, 0);
    cmd = pipecmd(cmd, parsepipe(ps, es));
  }
  return cmd;
}

struct cmd* parseredirs(struct cmd *cmd, char **ps, char *es) {
  int tok;
  char *q, *eq;

  while (peek(ps, es, "<>")) {
    tok = gettoken(ps, es, 0, 0);
    if (gettoken(ps, es, &q, &eq) != 'a') {
      fprintf(stderr, "missing file for redirection\n");
      exit(-1);
    }
    switch (tok) {
      case '<':
        cmd = redircmd(cmd, mkcopy(q, eq), '<');
      break;
      case '>':
        cmd = redircmd(cmd, mkcopy(q, eq), '>');
      break;
    }
  }
  return cmd;
}

struct cmd* parseexec(char **ps, char *es) {
  char *q, *eq;
  int tok, argc;
  struct execcmd* cmd;
  struct cmd* ret;

  ret = execcmd();
  cmd = (struct execcmd*)ret;
  
  argc = 0;
  ret = parseredirs(ret, ps, es);
  while (!peek(ps, es, "|")) {
    if ((tok=gettoken(ps, es, &q, &eq)) == 0)
      break;
    if (tok != 'a') {
      fprintf(stderr, "syntax error\n");
      exit(-1);
    }
    cmd->argv[argc] = mkcopy(q, eq);
    argc++;
    if (argc >= MAXARGS) {
      fprintf(stderr, "too many args\n");
      exit(-1);
    }
    ret = parseredirs(ret, ps, es);
  }
  cmd->argv[argc] = 0;
  return ret;
}
