#include <stdint.h>
#include "sync.h"
#include "process.h"
#include "console.h"
#include "start.h"

void end();

void _setup_thread_id();

int _get_sie();
void _write_sie(int64_t val);

int _get_mie();
void _write_mie(int64_t val);

uint64_t _read_mstatus();
void _write_mstatus(uint64_t val);

// bitmask for spp
const int64_t MSTATUS_SPP = (0x01) << 8;

#define MSTATUS_MPP_MASK (3L << 11) // previous mode.
#define MSTATUS_MPP_M (3L << 11)
#define MSTATUS_MPP_S (1L << 11)
#define MSTATUS_MPP_U (0L << 11)
#define MSTATUS_MIE (1L << 3)    // machine-mode interrupt enable.

#define SIE (1)
#define EIE (1L << 9) // external
#define TIE (1L << 5) // timer

__attribute__ ((aligned (16))) char stack[4096 * 5];
__attribute__ ((aligned (16))) volatile int current_printer;

int my_function(int a) 
{
  return a + 2;
}
void w_mepc(uint64_t x)
{
  asm volatile("csrw mepc, %0" : : "r" (x));
}

void w_satp(uint64_t x)
{
  asm volatile("csrw satp, %0" : : "r" (x));
}

// Supervisor Interrupt Enable
#define SIE_SEIE (1L << 9) // external
#define SIE_STIE (1L << 5) // timer
#define SIE_SSIE (1L << 1) // software
//
void start() {
  // previous mode was supervisor
  uint64_t status = _read_mstatus();
  status &= ~MSTATUS_MPP_MASK;
  status |= MSTATUS_MPP_S;
  _write_mstatus(status);
  _setup_thread_id();

  // enable timer interrupts
  _write_sie(_get_sie() | SIE_SSIE | SIE_SEIE | SIE_STIE);

  asm volatile("csrw pmpaddr0, %0" : : "r" (0x3fffffffffffffull));
  asm volatile("csrw pmpcfg0, %0" : : "r" (0xf));

  // delegate timers to supervisor mode
  asm volatile("csrs mideleg, %0": : "r" (0xffff));
  asm volatile("csrs mideleg, %0": : "r" (0xffff));

  asm volatile("csrw mepc, %0" : : "r" ((unsigned long) end));

  w_satp(0);
  asm volatile("mret");
}


