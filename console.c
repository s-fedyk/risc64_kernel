#include "console.h"
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
