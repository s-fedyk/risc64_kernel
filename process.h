#include <stdint.h>
// saved on context switch
typedef struct registers {
  uint64_t ra;
  uint64_t sp;
  uint64_t s0;
  uint64_t s1;
  uint64_t s2;
  uint64_t s3;
  uint64_t s4;
  uint64_t s5;
  uint64_t s6;
  uint64_t s7;
  uint64_t s8;
  uint64_t s9;
  uint64_t s10;
  uint64_t s11;
} registers;

typedef enum pstatus {
  RUNNING,
  RUNNABLE,
  SLEEPING,
  DEAD,
  ZOMBIE,
} pstatus;

struct process {
  char lock;
  pstatus status;
  // holds the context of execution
  registers reg;
};

// should only have one of these
struct process_table {
  struct process* processes;
  uint64_t nprocesses;
};


