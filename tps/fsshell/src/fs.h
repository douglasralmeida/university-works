/*
**	TP3 de SO
**	A1
**  A2
**
**/

#ifndef FS_H
#define FS_H

/* Tamanho do buffer da linha de comando atual */
#define SHBUFFER 100

typedef unsigned short uint16;

typedef unsigned int uint32;

struct ext2_super_block {
  uint32 inodes_count;          /* Contador de Inodes */
};

struct {
  char* imgnome;
  int   imgdesc;
  char  pwd[129];
} fs;

/****  COMANDOS DO SHELL  ****/

/* Quantidade de comandos */
#define SHCMDSMAX 1

/* Cabeçalho dos comandos */
void sh_cmd_pwd(void);

/* Estruturas para o vetor de comandos do shell */
typedef void (*shcmd)(void);

shcmd shcmds_func[SHCMDSMAX] = {
  &sh_cmd_pwd
};

/* Cada string deve estar na mesma posição da
   sua respectiva função em shcmds_func */
char* shcmds_name[SHCMDSMAX] = {
  "pwd"
};

static struct {
  shcmd* functions;
  char** names;
} shcmds;

int shcmds_lookup(char* cmd);

void shcmds_call(int index);

#endif
