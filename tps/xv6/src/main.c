//Kernel do xv6
//É chamado atraves de entry.S

#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "x86.h"

static void startothers(void);
static void mpmain(void)  __attribute__((noreturn));
extern pde_t *kpgdir;
extern char end[]; // primerio endereço após o kernel ser caregado do arquivo ELF

// Os procedimentos de inicialização começam a executar o 
// código .C a partir daqui.
// Aloca uma pilha real e troca para ela, primeiro fazendo
// algumas configurações necessárias par o alocador de memória funcionar.
int main(void) {
  kinit1(end, P2V(4*1024*1024)); // alocador de páginas de memória física
  kvmalloc();      // tabela de páginas do kernel
  mpinit();        // detecta outros processadores
  lapicinit();     // controlador de interrupções
  seginit();       // descritores de segmentos
  picinit();       // desabilita pic
  ioapicinit();    // outro controlador de interrupções
  consoleinit();   // console hardware
  uartinit();      // porta serial
  pinit();         // tabela de processos
  tvinit();        // vetores trap
  binit();         // buffer cache
  fileinit();      // tabela de arquivo
  ideinit();       // disco 
  startothers();   // inicia outros processadores
  kinit2(P2V(4*1024*1024), P2V(PHYSTOP)); // deve vir após startothers()
  userinit();      // primeiro processo no modo usuário
  mpmain();        // encerra esta configuração de processadores
}

// Other CPUs jump here from entryother.S.
static void mpenter(void) {
  switchkvm();
  seginit();
  lapicinit();
  mpmain();
}

// Código de configuração de CPU.
static void mpmain(void) {
  cprintf("cpu%d: iniciando %d\n", cpuid(), cpuid());
  idtinit();       // load idt register
  xchg(&(mycpu()->started), 1); // tell startothers() we're up
  scheduler();     // start running processes
}

pde_t entrypgdir[];  // For entry.S

// Start the non-boot (AP) processors.
static void startothers(void) {
  extern uchar _binary_entryother_start[], _binary_entryother_size[];
  uchar *code;
  struct cpu *c;
  char *stack;

  // Write entry code to unused memory at 0x7000.
  // The linker has placed the image of entryother.S in
  // _binary_entryother_start.
  code = P2V(0x7000);
  memmove(code, _binary_entryother_start, (uint)_binary_entryother_size);

  for(c = cpus; c < cpus+ncpu; c++){
    if(c == mycpu())  // We've started already.
      continue;

    // Tell entryother.S what stack to use, where to enter, and what
    // pgdir to use. We cannot use kpgdir yet, because the AP processor
    // is running in low  memory, so we use entrypgdir for the APs too.
    stack = kalloc();
    *(void**)(code-4) = stack + KSTACKSIZE;
    *(void**)(code-8) = mpenter;
    *(int**)(code-12) = (void *) V2P(entrypgdir);

    lapicstartap(c->apicid, V2P(code));

    // wait for cpu to finish mpmain()
    while(c->started == 0)
      ;
  }
}

// The boot page table used in entry.S and entryother.S.
// Page directories (and page tables) must start on page boundaries,
// hence the __aligned__ attribute.
// PTE_PS in a page directory entry enables 4Mbyte pages.

__attribute__((__aligned__(PGSIZE)))
pde_t entrypgdir[NPDENTRIES] = {
  // Map VA's [0, 4MB) to PA's [0, 4MB)
  [0] = (0) | PTE_P | PTE_W | PTE_PS,
  // Map VA's [KERNBASE, KERNBASE+4MB) to PA's [0, 4MB)
  [KERNBASE>>PDXSHIFT] = (0) | PTE_P | PTE_W | PTE_PS,
};
