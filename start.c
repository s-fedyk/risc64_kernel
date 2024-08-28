#include <stdint.h>
#include "sync.h"
#include "process.h"
#include "console.h"
#include "start.h"

int _get_hart_id();

// make this visible
__attribute__ ((aligned (16))) char stack[4096 * 5];
__attribute__ ((aligned (16))) volatile int current_printer;
__attribute__ ((aligned (16))) char lock = 0;

int my_function(int a) {
  return a + 2;
}

int start() {
  int this_hart = _get_hart_id();

  char mstring[] = {'h','a','r','t',' ', '#',' ','\0'};
  char nl[] = {'\n','\0'};

  while(_try_lock(&lock)) ;

  write_string(mstring);
  write_integer(this_hart);
  write_string(nl);

  _release_lock(&lock);

  return 0;
}
