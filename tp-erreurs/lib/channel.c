#include <stdlib.h>

#include "channel.h"

char cbssm(char byte, float proba) {
  int i;
  for (i = 0; i < 8; i++) {
    if (rand() / ((float) RAND_MAX+1) < proba)
      byte ^= (1 << i);
  }
  return byte;
}
