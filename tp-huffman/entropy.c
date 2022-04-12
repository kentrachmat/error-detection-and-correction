#include<stdio.h>
#include<stdlib.h>

#include "lib/entropy_lib.h"

int main(int argc, char **argv) {

  if (argc <= 1) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(1);
  }
  FILE *file = fopen(argv[1], "r");
  //8<-----------------------------
  int counts[256];
  int i;
  for (i = 0; i < 256; i++) {
    counts[i] = 0;
  }

  count_occurrences(file, counts);
  struct file_stat stat = entropy(counts);

  
  printf("Le fichier fait %d octets et a une entropie de %.2f bits par octet\n", stat.size, stat.entropy);
  printf("Au mieux un codage optimal améliorerait le stockage de ce fichier de %.0f%%.\n", (8 - stat.entropy)*100. / 8);
  //----------------------------->8
  /* À COMPLÉTER */

  fclose(file);
  exit(0);
}
