#include <stdint.h>
#include "console.h"

uint64_t _get_interrupt_cause();

void interrupt_handle_supervisor() {
  char string[] = "handling an interrupt";
  uint64_t cause = _get_interrupt_cause();
  write_string(string);
  write_integer(cause);
}
