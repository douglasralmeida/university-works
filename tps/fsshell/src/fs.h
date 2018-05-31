/*
**	TP3 de SO
**	A1
**  A2
**
**/

#ifndef FS_H
#define FS_H

typedef unsigned short uint16;

typedef unsigned int uint32;

/****  EXT2  ****/

struct ext2_super_block {
  uint32 inodes_count;          /* Contador de Inodes */
};

/****  FS  ****/

struct {
  char* imgnome;
  int   imgdesc;
  char  pwd[129];
} fs;

/****  SHELL  ****/

/* Tamanho do buffer da linha de comando atual */
#define SHBUFFER 257

/* Tamanho do buffer de um comando */
#define SHCMDBUFFER 17

/* Quantidade de comandos */
#define SHCMDSQUANT 1

/* Cabeçalho dos comandos do shell */
void sh_cmd_pwd(void);

/* Estruturas para o vetor de comandos do shell */
typedef void (*shcmd_t)(void);

shcmd_t shcmds_func[SHCMDSQUANT] = {
  &sh_cmd_pwd
};

/* Cada string deve estar na mesma posição da
   sua respectiva função em shcmds_func */
char* shcmds_name[SHCMDSQUANT] = {
  "pwd"
};

struct {
  shcmd_t* functions;
  char** names;
} shcmds;

struct {
  char cmd[SHCMDBUFFER];
  char* arg;
} usercmd;

void shcmds_call(int index);

int shcmds_lookup(char* cmd);

/* Funções do shell */
int sh_getcmd(char *buf, int nbuf);

void sh_init();

void sh_parse(char* line);

void sh_run();

#endif
