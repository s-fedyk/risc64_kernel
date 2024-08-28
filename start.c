#include <stdint.h>

int _get_hart_id();
// make this visible
__attribute__ ((aligned (16))) char stack[4096 * 5];

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

int start() {
  char mstring[] = {'f','a','t', ' ', 'c', 'u','n','t','1','\n','\0'};
  write_string(mstring);
  write_integer(_get_hart_id());
  while (1) ;
}
