#include <stdio.h>

#include "repeat.h"
#include "../tests/tests.h"

void encode_repeat() {
  int byte;
  while ((byte = getchar()) != EOF) {
    putchar(byte);
    putchar(byte);
    putchar(byte);
  }
}

unsigned char decode_three_bytes(unsigned char bytes[3]) {
  return ((bytes[0] & bytes[1]) | (bytes[1] & bytes[2]) | (bytes[0] & bytes[2]));
}

void decode_repeat() {
  unsigned char bytes[3];
  int byte;
  int fini = 0;
  int i;
  while (! fini) {
    for (i = 0; i < 3 && ! fini; i++) {
      byte = getchar();
      if (byte == EOF)
        fini = 1;
      else
        bytes[i] = byte;
    }
    if (! fini) {
      putchar(decode_three_bytes(bytes));
    }
  }
}
