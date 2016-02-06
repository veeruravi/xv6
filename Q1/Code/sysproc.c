#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
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
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
/*
int
sys_waitx(int *x,int *y)
{
  cprintf("c_time: %d\n",cpu->proc->c_time);
  cprintf("rtime: %d\n",cpu->proc->rtime);
  cprintf("etime: %d\n",cpu->proc->rtime+cpu->proc->c_time);
  
  return wait();
}
*/
int
sys_waitx(int *x,int *y)
{
  int a,b;
  //int a1,b1;
  argint(0,&a);
  //fetchint(a,&a1);
  argint(1,&b);
  *((int *)a)=ticks-cpu->proc->c_time-cpu->proc->rtime;
  *((int *)b)=cpu->proc->rtime; 
  //fetchint(b,&b1);
  //cprintf("%d %d\n", a1,b1);
  //cprintf("%d %d\n",cpu->proc->rtime,cpu->proc->iotime);
  //int totTime=cpu->proc->rtime;
  //cprintf("%d MY\n", cpu->proc->pid);
  //int totSleepTime=cpu->proc->wtime;
  //cprintf("c_time: %d\n",cpu->proc->c_time);
  //cprintf("rtime: %d\n",cpu->proc->rtime);
  //cprintf("etime: %d\n",cpu->proc->rtime+cpu->proc->c_time);
  //cprintf("wtime: %d\n",cpu->proc->wtime);
  return wait();
}
