#include <stdio.h>
#include <stdlib.h>
#include "lib/binary_matrix.h"
#include "lib/linear_coding.h"
#include "lib/generator_matrices.h"

int main(void) {
  binary_matrix g = parity_generator(4);
  binary_matrix w = zero_matrix(1, 4);
  binary_matrix result, s, tH;

  if (! g) {
    fprintf(stderr, "Invalid generator matrix for parity coding\n");
    exit(1);
  }
  
  set_matrix_value(w, 0, 1, 1);
  set_matrix_value(w, 0, 2, 1);

  printf("Generator matrix for parity coding [5, 4, 2]\n");
  print_matrix(g);

  printf("Word\n");
  print_matrix(w);

  printf("Result of the coding\n");
  result = code_word(w, g);
  print_matrix(result);


  tH = transposed_control_matrix(g);
  if (tH) {
    printf("Transposed control matrix\n");
    print_matrix(tH);
    
    s = syndrome(result, tH);
    if (s) {
      printf("Syndrome for ");
      print_matrix(result);
      print_matrix(s);

      set_matrix_value(result, 0, 0, 1-matrix_value(result, 0, 0));
      destroy_matrix(s);
      s = syndrome(result, tH);
      printf("Syndrome for ");
      print_matrix(result);
      print_matrix(s);
      destroy_matrix(s);
    }

    destroy_matrix(tH);
  }
  destroy_matrix(g);
  if (result)
    destroy_matrix(result);

  printf("--------------------------------------------------\n");

  g = repeat3_generator(4);

  if (! g) { 
    fprintf(stderr, "Invalid generator matrix for repeat coding\n");
    exit(1);
  }

  printf("Generator matrix for repeat coding [12, 4, 3]\n");
  print_matrix(g);

  printf("Word\n");
  print_matrix(w);

  printf("Result of the coding\n");
  result = code_word(w, g);
  print_matrix(result);

  tH = transposed_control_matrix(g);
  if (tH) {
    printf("Transposed control matrix\n");
    print_matrix(tH);
    
    s = syndrome(result, tH);
    if (s) {
      printf("Syndrome for ");
      print_matrix(result);
      print_matrix(s);

      set_matrix_value(result, 0, 0, 1-matrix_value(result, 0, 0));
      destroy_matrix(s);
      s = syndrome(result, tH);
      printf("Syndrome for ");
      print_matrix(result);
      print_matrix(s);
      printf("Corrected word: ");
      print_matrix(correct_result(result, s, tH));
      destroy_matrix(s);
    }

    destroy_matrix(tH);
  }

  destroy_matrix(g);
  if (result)
    destroy_matrix(result);
  destroy_matrix(w);
  return 0;
}
