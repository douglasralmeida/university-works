/*
**	TP3 de SO
**	A1
**  A2
**
**/

#ifndef FS_H
#define FS_H

typedef unsigned char uint8;

typedef unsigned short uint16;

typedef unsigned int uint32;

/*#define SHOW_DEBUGINFO 0*/

/****  EXT2  ****/

/* espaço para o setor de inicialização no HD */
#define BOOT_OFFSET 1024

#define BLOCK_SIZE(x) \
  (1024 << x)

/* tamanho máximo de um nome de arquivo */
#define EXT2_NAME_LEN 255

/* offset entre dir_entry e dir_entry->name */
#define EXT2_NAME_OFFSET 8

/* número mágico do ext2 */
#define EXT2_SUPER_MAGIC 0xEF53

/* quantidade de blocos de dados */
#define	EXT2_NDIR_BLOCKS 12
#define	EXT2_IND_BLOCK EXT2_NDIR_BLOCKS
#define	EXT2_DIND_BLOCK  (EXT2_IND_BLOCK + 1)
#define	EXT2_TIND_BLOCK  (EXT2_DIND_BLOCK + 1)
#define	EXT2_N_BLOCKS    (EXT2_TIND_BLOCK + 1)

/* Nós i especiais */

/* nó i do diretório raiz */
#define EXT2_ROOT_INO	2

/* Flags do nó i */
#define EXT2_INDEX_FL 0x00001000   /* diretório com índice hash */

/* estrutura do superbloco
 *
 * um superbloco tem 1024 bytes. ele contém metadados
 * do sistema de arquivos. os metadados formam um
 * vetor de inteiros, alguns de 16 bits, outros de 32 bits.
 */
typedef struct e_sblk {
  uint32 inodes_count;          /* contador de nós i                       */
  uint32 reserved1[5];          /* não utilizado neste TP                  */
  uint32 log_block_size;        /* tamanho de cada bloco                   */
  uint32 log_frag_size;         /* tamanho de cada fragmento               */
  uint32 blocks_per_group;      /* quant. de blocos por grupo              */
  uint32 frags_per_group;       /* quant. de fragmentos por grupo          */
  uint32 inodes_per_group;      /* quant. de nós i em cada grupo de blocos */
  uint32 reserved2[3];          /* não utilizado neste TP                  */
  uint16 magic;                 /* assinatura mágica do ext2               */
  uint16 state;                 /* estado atual do fs                      */
  uint32 reserved3[7];          /* não utilizado neste TP                  */
  uint16 inode_size;            /* tamanho da estrutura ext2_inode         */
  uint16 block_group_nr;        /* num. do grupo de blocos que hospeda este superbloco */
  uint32 reserved4[233];        /* não utilizado neste TP                  */
} ext2_super_block;

/* descritores do grupo de blocos
 *
 * os descritores do grupo de blocos tem 32 bytes. ele contém metadados
 * do grupo ao qual pertence. os metadados formam um
 * vetor de inteiros, alguns de 16 bits, outros de 32 bits.
 */
typedef struct e_gdesc {
  uint32 reserved1[2];          /* não utilizado neste TP                       */
  uint32 inode_table;           /* endereço do bloco da tabela de nós i         */
  uint32 reserved2[5];          /* não utilizado neste TP                       */
} ext2_group_desc;

/* nó i
 *
 * o nó i tem 128 bytes. ele contém metadados de um arquivo.
 * os metadados formam um vetor de inteiros, alguns de 8 bits,
 * outros de 16 bits e outros de 32 bits.
 */
typedef struct e_in {
  uint16 mode;                   /* modos do arquivo                              */
  uint16 uid;                    /* uid do dono do arquivo                        */
  uint32 size;                   /* tamanho do arquivo                            */
  uint32 reserved2[5];           /* não utilizado neste TP                        */
  uint32 blocks;                 /* total de blocos de dados reservados pelo nó-i */
  uint32 flags;                  /* metadados do nó i                       */
  uint32 reserved3;              /* não utilizado neste TP                        */
  uint32 block[EXT2_N_BLOCKS];   /* ponteiros para os blocos                */
  uint32 reserved4[7];           /* não utilizado neste TP                  */
} ext2_inode;

/* entrada de diretório
 * 
 * a entrada de diretório tem 262 bytes. ela contém a descrição
 * de cada item de um diretório dado. a descrição forma um vetor
 * de inteiros, alguns de 8 bits, outros de 16 bits e outros de 32
 * bits.
 */
typedef struct e_dentry {
	uint32 inode;         /* número do nó i */
	uint16 rec_len;	      /* tamanho da entrada de diretório */
	uint8  name_len;      /* tamanho do nome da entrada */
	uint8  file_type;     /* tipo da entrada */
	char*	 name;          /* nome da entrada (max. 255)(não usar diretamente) */
} ext2_dir_entry;


/****  FS  ****/

typedef struct dt {
  ext2_inode*       data;         /* metadados do diretório */
  uint32            inode;        /* nó i do diretório */
} dir_t;

/* Tamanho máximo do caminho do diretório atual */
#define MAX_PATH 8192

struct {
  char*             imgname;      /* nome do arquivo de imagem           */
  int               imgdesc;      /* descritor (fd) do arquivo de imagem */
  dir_t             curr_dir;     /* diretório atual                     */
  char              pwd[MAX_PATH];/* caminho do diretório atual          */
  void*             ptr;          /* ponteiro para o arquivo img mapeado */
  off_t             size;         /* tamanho do arquivo de imagem        */
  ext2_super_block* super_block;  /* ponteiro para o primeiro superbloco */
  uint32            block_size;   /* tamanho padrão de um bloco          */
} fs;

/* estrutura para interação com as entradas de diretório */
typedef int (*direntry_func_t)(ext2_dir_entry*, void*);

/* exibe o nome da entrada de diretório na tela */
int fs_direntry_show(ext2_dir_entry* entry, void* data);

/* escolhe a entrada de diretório como diretório atual */
int fs_direntry_goto(ext2_dir_entry* entry, void* data);

/****  SHELL  ****/

/* Tamanho do buffer da linha de comando atual */
#define SHBUFFER 512

/* Quantidade máxima de argumentos de um comando */
#define ARG_MAX 4096

/* Quantide máxima de subdiretório passados pelo comando cd */
#define CD_PATH_MAX 256

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

typedef struct cdinfo {
  uint32 inode_index;
  ext2_inode* inode_data;
  char* nextdir;
  int isnotdir;
} cdinfo_t;

#endif
