// Mutual exclusion lock.
struct spinlock {
  uint locked;       // Is the lock held?

  // For debugging:
  char *name;        // Name of lock.
  struct cpu *cpu;   // The cpu holding the lock.
  uint pcs[10];      // The call stack (an array of program counters)
                     // that locked the lock.
};


int sh_var_for_sem_demo;

#define SEM_MAX_NUM 120
extern int sem_used_count;

struct sem {
  struct spinlock lock;
  int resource_count;
  int allocated;
};
extern struct sem sems[SEM_MAX_NUM];