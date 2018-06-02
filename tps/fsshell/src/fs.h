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

/*
   um superbloco tem 1024 bytes. ele contém metadados
   do bloco no qual pertence. os metadados formam um
   vetor de inteiros, alguns de 16 bits, outros de 32 bits.
*/
/* estrutura do superbloco */
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
  char*             imgname;      /* nome do arquivo de imagem           */
  int               imgdesc;      /* descritor (fd) do arquivo de imagem */
  char              pwd[129];     /* diretório atual                     */
  void*             ptr;          /* ponteiro para o arquivo img mapeado */
  off_t             size;         /* tamanho do arquivo de imagem        */
  ext2_super_block* super_block;  /* ponteiro para um superbloco         */
  uint32            block_size;   /* tamanho padrão de um bloco          */
} fs;

/****  SHELL  ****/

/* Tamanho do buffer da linha de comando atual */
#define SHBUFFER 512

/* Quantidade máxima de argumentos de um comando */
#define ARG_MAX 4096

/* Quantidade de comandos */
#define SHCMDSQUANT 8

/* Cabeçalho dos comandos do shell */

void sh_cmd_info(void);

void sh_cmd_cd(void);

void sh_cmd_exit(void);

void sh_cmd_find(void);

void sh_cmd_ls(void);

void sh_cmd_pwd(void);

void sh_cmd_sb(void);

void sh_cmd_stat(void);

/* Estruturas para o vetor de comandos do shell */
typedef void (*shcmd_t)(void);

shcmd_t shcmds_func[SHCMDSQUANT] = {
  &sh_cmd_info,
  &sh_cmd_cd,
  &sh_cmd_exit,
  &sh_cmd_find,
  &sh_cmd_ls,
  &sh_cmd_pwd,
  &sh_cmd_sb,
  &sh_cmd_stat
};

/* Cada string deve estar na mesma posição da
   sua respectiva função em shcmds_func */
char* shcmds_name[SHCMDSQUANT] = {
  "info",
  "cd",
  "exit",
  "find",
  "ls",
  "pwd",
  "sb",
  "stat"
};

struct {
  shcmd_t* functions;
  char** names;
} shcmds;

struct {
  int argc;
  char* argv[ARG_MAX];
  int exiting;
} usercmd;

void shcmds_call(int index);

int shcmds_lookup(char* cmd);

/* Funções do shell */
int sh_getcmd(char *buf, int nbuf);

void sh_init();

void sh_parse(char* line);

void sh_run();

#endif
