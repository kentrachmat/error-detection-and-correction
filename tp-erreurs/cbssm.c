#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/channel.h"

int main(int argc, char **argv) {
  int byte;
  float proba;
  if (argc < 2) {
    fprintf(stderr, "Usage: %s proba\n\nproba: Probability of error (between 0 and 1)\n", argv[0]);
    exit(1);
  }
  srand(time(NULL));

  proba = atof(argv[1]);

  while ((byte = getchar()) != EOF) {
    putchar(cbssm(byte, proba));
  }

  return 0;
}
