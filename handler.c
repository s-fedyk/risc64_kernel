#include <stdint.h>
#include "console.h"

uint64_t _get_interrupt_cause();

__attribute__((interrupt ("supervisor")))
void interrupt_handle_supervisor(void) {
  uint64_t cause = _get_interrupt_cause();
  write_integer(cause);
}
