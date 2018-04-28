// estado de uma CPU
struct cpu {
  uchar apicid;                // Local APIC ID
  struct context *scheduler;   // swtch() here to enter scheduler
  struct taskstate ts;         // Used by x86 to find stack for interrupt
  struct segdesc gdt[NSEGS];   // x86 global descriptor table
  volatile uint started;       // Has the CPU started?
  int ncli;                    // Depth of pushcli nesting.
  int intena;                  // Were interrupts enabled before pushcli?
  struct proc *proc;           // The process running on this cpu or null
};

extern struct cpu cpus[NCPU];
extern int ncpu;

// Registradores salvos para trocas de contexto do kernel.
// Don't need to save all the segment registers (%cs, etc),
// because they are constant across kernel contexts.
// Don't need to save %eax, %ecx, %edx, because the
// x86 convention is that the caller has saved them.
// Contexts are stored at the bottom of the stack they
// describe; the stack pointer is the address of the context.
// The layout of the context matches the layout of the stack in swtch.S
// at the "Switch stacks" comment. Switch doesn't save eip explicitly,
// but it is on the stack and allocproc() manipulates it.
struct context {
  uint edi;
  uint esi;
  uint ebx;
  uint ebp;
  uint eip;
};

enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

// estado de um processo
struct proc {
  uint sz;                     // Tamanho da memória do processo (bytes)
  pde_t* pgdir;                // Tabela de Páginas
  char *kstack;                // Bottom of kernel stack for this process
  enum procstate state;        // Estado do processo
  int pid;                     // ID Processo
  struct proc *parent;         // Processo pai
  struct trapframe *tf;        // Moldura trap para a chamada de sistema atual
  struct context *context;     // swtch() aqui para executar o processo
  void *chan;                  // If non-zero, sleeping on chan
  int killed;                  // Se não for zero, mòr-reu!!
  struct file *ofile[NOFILE];  // Abertura de arquivos
  struct inode *cwd;           // Diretório atual
  char name[16];               // Nome do processo (para depuração)
};

// Process memory is laid out contiguously, low addresses first:
//   text
//   original data and bss
//   fixed-size stack
//   expandable heap
