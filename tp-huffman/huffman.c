#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "lib/huffman_algo.h"

int main(int argc, char **argv) {
  if (argc <= 3) {
    fprintf(stderr, "Usage: %s [-c|-d] <input> <output>\n\n-c: compress\n-d: uncompress", argv[0]);
    exit(1);
  }

  if (strcmp(argv[1], "-c") == 0) {
    huffman_coding(argv[2], argv[3], 0);
  } else if (strcmp(argv[1], "-d") == 0) {
    
    huffman_decoding(argv[2], argv[3], 0);
    
  }
  exit(0);
}
