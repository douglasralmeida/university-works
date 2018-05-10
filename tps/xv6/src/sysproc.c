#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "stdlib.h"

int sys_fork(void) {
  return fork();
}

int sys_exit(void) {
  exit();
  return 0;  // não alcançado
}

int sys_wait(void) {
  return wait();
}

int sys_kill(void) {
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
    
  return kill(pid);
}

int sys_getpid(void) {
  return myproc()->pid;
}

int sys_sbrk(void) {
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
    
  return addr;
}

int sys_sleep(void) {
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n) {
    if (myproc()->killed) {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void) {
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  
  return xticks;
}


//SYSCALL implementado
//retorna a data do sistem
int sys_date(void) {
  char *ptr;

  if (argptr(0, &ptr, sizeof(struct rtcdate*)) < 0)
    return -1;
  cmostime((struct rtcdate*)ptr);

  return 0;
}

//SYSCALLs do TP

//converte endereços de memória virtual em endereços de memória real
int sys_virt2real(void) {
  char* endereco;
  
  if (argstr(0, &endereco) < 0)
    return -1;
    
  return (int)va2pa((uint*)endereco);
}

//retorna o numero de páginas utilizadas pelo processo atual
int sys_num_pages(void) {   
  return (int)countpages();
}

//faz um fork com copy-on-write
int sys_forkcow(void) {
   return forkcow();
}
