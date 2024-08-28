#include <stdint.h>
#include "start.h"

int _get_hart_id();
// make this visible
__attribute__ ((aligned (16))) char stack[4096 * 5];
__attribute__ ((aligned (16))) volatile int current_printer;

void write_string(char *mstring) {
  uint8_t i = 0;
  while (mstring[i] != '\0') {
    *(((volatile unsigned char *)(0x10000000L))) = mstring[i];
    i+=1;
  }
  return;
}

void write_integer(uint64_t mnumber) {
  *(((volatile unsigned char *)(0x10000000L))) = (char)(mnumber + 48);
  return;
}

int my_function(int a) {
  return a + 2;
}

int start() {
  int this_hart = _get_hart_id();

  char mstring[] = {'h','a','r','t',' ', '#',' ','\0'};
  char nl[] = {'\n','\0'};

  while(current_printer != this_hart) ;

  write_string(mstring);
  write_integer(this_hart);
  write_string(nl);

  current_printer+=1;

  return 0;
}
