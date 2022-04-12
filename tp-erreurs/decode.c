#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/generator_matrices.h"
#include "lib/linear_coding.h"
#include "lib/repeat.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s method\n\nmethod: method used for encoding (repeat3, repeat3-linear parity2d, hamming, hammingp)\n", argv[0]);
    exit(1);
  }

  if (strcmp(argv[1], "repeat3") == 0) {
    decode_repeat();
  } 
  else if (strcmp(argv[1], "repeat3-linear") == 0) {
    linear_decoding(transposed_control_matrix(repeat3_generator(20)));
  } else if (strcmp(argv[1], "parity2d") == 0) {
    linear_decoding(transposed_control_matrix(parity2d_generator()));
  } else if (strcmp(argv[1], "hamming") == 0) {
    linear_decoding(transposed_control_matrix(hamming_generator()));
  } else if (strcmp(argv[1], "hammingp") == 0) {
    linear_decoding(transposed_control_matrix(hammingp_generator()));
  } 
  else {
    fprintf(stderr, "Method %s is unknown or not yet implemented\n", argv[1]);
    exit(1);
  }
  return 0;
}
