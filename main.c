
#include <stdint.h>
void write_string(char *mstring) {
  uint8_t i = 0;
  while (mstring[i] != '\0') {
    (*(((volatile unsigned char *)(0x10000000L))) = mstring[i]);
    i+=1;
  }
  return;
}

int start() {
  char mstring[] = {'f','a','t', ' ', 'c', 'u','n','t','1','\0'};
  write_string(mstring);

  while (1) ;
}
