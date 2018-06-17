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

/* versões do ext2 */
#define EXT2_GOOD_OLD_REV	0	/* versão original */

#define EXT2_DYNAMIC_REV	1 	/* versão 2 com tamanhos dinâmicos de nó i */

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
  uint32 blocks_count;
  uint32 r_blocks_count;
  uint32 free_blocks_count;
  uint32 free_inodes_count;
  uint32 first_data_block;
  uint32 log_block_size;        /* tamanho de cada bloco                   */
  uint32 log_frag_size;         /* tamanho de cada fragmento               */
  uint32 blocks_per_group;      /* quant. de blocos por grupo              */
  uint32 frags_per_group;       /* quant. de fragmentos por grupo          */
  uint32 inodes_per_group;      /* quant. de nós i em cada grupo de blocos */
  uint32 mtime;
  uint32 wtime;
  uint16 mnt_count;
  uint16 max_mnt_count;         
  uint16 magic;                 /* assinatura mágica do ext2               */
  uint16 state;                 /* estado atual do fs                      */
  uint16 errors;
  uint16 minor_rev_level;
  uint32 lastcheck;
  uint32 checkinterval;
  uint32 creator_os;
  uint32 rev_level;
  uint16 def_resuid;
  uint16 def_resgid;
  uint32 first_ino;
  uint16 inode_size;            /* tamanho da estrutura ext2_inode         */
  uint16 block_group_nr;        /* num. do grupo de blocos que hospeda este superbloco */
  uint32 feature_compat;
	uint32 feature_incompat;
  uint32 feature_ro_compat;
  uint8 uuid[16];
	uint8 volume_name[16];
	uint8 last_mounted[64];
	uint32 algorithm_usage_bitmap;
  uint8	prealloc_blocks;
	uint8	prealloc_dir_blocks;
	uint16 padding1;
	
	uint8 journal_uuid[16];
	uint32 journal_inum;
	uint32 journal_dev;
	uint32 last_orphan;
	uint32 hash_seed[4];
	uint8 def_hash_version;
	uint8 reserved_char_pad;
	uint16 reserved_word_pad;
	uint32 default_mount_opts;
 	uint32 first_meta_bg;
  uint32 reserved4[190];        /* reservado                  */
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
  uint32 atime;                  /* nº segundos desde o último acesso ao nó i     */
  uint32 ctime;                  /* nº segundos desde a criação do nó i           */
  uint32 mtime;                  /* nº segundos desde a última modificação ao nó i*/
  uint32 dtime;                  /* nº segundos desde a exclusão do nó i          */
  uint16 gid;                    /* gid do grupo que acessa o arquivo             */
  uint16 links_count;            /* nº de referências (atalhos) para o nó i       */
  uint32 blocks;                 /* total de blocos de dados reservados pelo nó-i */
  uint32 flags;                  /* metadados do nó i                             */
  uint32 reserved3;              /* não utilizado neste TP                        */
  uint32 block[EXT2_N_BLOCKS];   /* ponteiros para os blocos                      */
  uint32 reserved4[7];           /* não utilizado neste TP                        */
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


/* modos do nó i
 * 
 * nó i->modo.
 */

char* ext2_inode_type[8] = {
  "fifo",
  "disp. caractere",
  "diretório",
  "dispositivo de bloco",
  "arquivo",
  "link",
  "soquete",
  "desconhecido"
};

enum ext2_inode_mode {
  IFMT    = 0xF000, /* Format mask */
  IFSOCK  = 0xA000, /* Socket. */
  IFLNK   = 0xC000, /* Symbol link. */
  IFREG   = 0x8000, /* Regular file. */
  IFBLK   = 0x6000, /* Block device. */
  IFDIR   = 0x4000, /* Directory. */
  IFCHR   = 0x2000, /* Character device. */
  IFIFO   = 0x1000, /* FIFO. */
  
  
  ISUID   = 0x0800, /* SUID. */
  ISGID   = 0x0400, /* SGID. */
  ISVTX   = 0x0200, /* Sticky bit. */
  
  IRWXU   = 0x01C0, /* User mask. */
  IRUSR   = 0x0100, /* Read. */
  IWUSR   = 0x0080, /* Write. */
  IXUSR   = 0x0040, /* Execute. */
  IRWXG   = 0x0038, /* Group mask. */
  IRGRP   = 0x0020, /* Read. */
  IWGRP   = 0x0010, /* Write. */
  IXGRP   = 0x0008, /* Execute. */
  IRWXO   = 0x0007, /* Other mask. */
  IROTH   = 0x0004, /* Read. */
  IWOTH   = 0x0002, /* Write. */
  IXOTH   = 0x0001  /* Execute. */
};

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

/*  */
int fs_interatedir(direntry_func_t action, ext2_inode* inode, void* data);

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

uint32 sh_getinode(char* path);

void sh_init();

void sh_parse(char* line);

void sh_run();

/* Funções usadas pelos comandos do shell */

void do_stat(uint32, ext2_inode*, char*);

typedef struct ii {
  uint32 inode;
  char* name;
} inodeinfo_t;

typedef struct ci {
  uint32 inode_index;
  ext2_inode* inode_data;
  char* nextdir;
  int isnotdir;
} cdinfo_t;


#endif
