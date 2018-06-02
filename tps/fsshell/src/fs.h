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

/* espaço do setor de inicialização no HD */
#define BOOT_OFFSET 1024

#define BLOCK_SIZE(x) \
  (1024 << x)

/* número mágico do ext2 */
#define EXT2_SUPER_MAGIC 0xEF53

typedef struct e_sblk {
  uint32 inodes_count;          /* contador de nós i          */
  uint32 reserved1[5];          /* não utilizado neste TP     */
  uint32 log_block_size;        /* tamanho do bloco           */
  uint32 reserved2[7];          /* não utilizado neste TP     */
  uint16 magic;                 /* assinatura mágica do ext2  */
  uint16 state;                 /* estado atual do fs         */
  uint32 reserved3[241];        /* não utilizado neste TP     */
} ext2_super_block;

/****  FS  ****/

struct {
  char*             imgname;
  int               imgdesc;
  char              pwd[129];
  void*             ptr;
  off_t             size;
  ext2_super_block* super_block;
  uint32            block_size;
} fs;

/****  SHELL  ****/

/* Tamanho do buffer da linha de comando atual */
#define SHBUFFER 257

/* Tamanho do buffer de um comando */
#define SHCMDBUFFER 17

/* Quantidade de comandos */
#define SHCMDSQUANT 2

/* Cabeçalho dos comandos do shell */
void sh_cmd_pwd(void);

void sh_cmd_info(void);

/* Estruturas para o vetor de comandos do shell */
typedef void (*shcmd_t)(void);

shcmd_t shcmds_func[SHCMDSQUANT] = {
  &sh_cmd_info,
  &sh_cmd_pwd
};

/* Cada string deve estar na mesma posição da
   sua respectiva função em shcmds_func */
char* shcmds_name[SHCMDSQUANT] = {
  "info",
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
