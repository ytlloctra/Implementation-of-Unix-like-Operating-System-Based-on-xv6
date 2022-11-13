#include "syscall.h"
#include "traps.h"

#define SYSCALL(name) \
  .globl name; \
  name: \
    movl $SYS_ ## name, %eax; \
    int $T_SYSCALL; \
    ret

SYSCALL(fork)
SYSCALL(exit)
SYSCALL(wait)
SYSCALL(pipe)
SYSCALL(read)
SYSCALL(write)
SYSCALL(close)
SYSCALL(kill)
SYSCALL(exec)
SYSCALL(open)
SYSCALL(mknod)
SYSCALL(unlink)
SYSCALL(fstat)
SYSCALL(link)
SYSCALL(mkdir)
SYSCALL(chdir)
SYSCALL(dup)
SYSCALL(getpid)
SYSCALL(sbrk)
SYSCALL(sleep)
SYSCALL(uptime)
SYSCALL(getcpuid)
SYSCALL(chpri)
SYSCALL(sh_var_read)
SYSCALL(sh_var_write)
SYSCALL(sem_create)
SYSCALL(sem_free)
SYSCALL(sem_p)
SYSCALL(sem_v)
SYSCALL(shmgetat)
SYSCALL(shmrefcount)

SYSCALL(mqget)		#messagequeuq.c
SYSCALL(msgsnd)
SYSCALL(msgrcv)
SYSCALL(myalloc)
SYSCALL(myfree)

SYSCALL(clone)
SYSCALL(join)