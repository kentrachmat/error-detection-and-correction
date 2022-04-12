#include <stddef.h>
#include "generator_matrices.h"

binary_matrix parity_generator(int n) {
  binary_matrix g = zero_matrix(n, n+1);
  int i;

  for (i = 0; i < n; i++) {
    set_matrix_value(g, i, i, 1);
    set_matrix_value(g, i, n, 1);
  }

  return g;
}

binary_matrix repeat3_generator(int n) {
  binary_matrix zeroMatrix = zero_matrix(n, 3*n);
  int j, i, res = 0;
  for(i=0; i<3; res+=n, i++){
    for(j=0; j<n; j++){
      set_matrix_value(zeroMatrix, j, j+res, 1);
    }
  }
  return zeroMatrix;
}

binary_matrix parity2d_generator(){
  binary_matrix matrix = zero_matrix(4,9);
  set_matrix_row(matrix ,0 ,1 ,0 ,0 ,0 ,1, 0, 1 ,0 ,1);
  set_matrix_row(matrix ,1 ,0 ,1 ,0 ,0 ,1, 0, 0 ,1 ,1);
  set_matrix_row(matrix ,2 ,0 ,0 ,1 ,0 ,0, 1, 1 ,0 ,1);
  set_matrix_row(matrix ,3 ,0 ,0 ,0 ,1 ,0, 1, 0 ,1 ,1);
  return matrix;
}

binary_matrix hamming_generator() {
  binary_matrix matrix = zero_matrix(4,7);
  set_matrix_row(matrix ,0 ,1 ,0 ,0 ,0 ,1, 1 ,0);
  set_matrix_row(matrix ,1 ,0 ,1 ,0 ,0 ,0, 1 ,1);
  set_matrix_row(matrix ,2 ,0 ,0 ,1 ,0 ,1 ,0 ,1);
  set_matrix_row(matrix ,3 ,0 ,0 ,0 ,1 ,1 ,1 ,1);
  return matrix;
}

binary_matrix hammingp_generator() {
  binary_matrix matrix = zero_matrix(4,8);
  set_matrix_row(matrix ,0 ,1 ,0 ,0 ,0 ,1 ,1 ,0 ,1);
  set_matrix_row(matrix ,1 ,0 ,1 ,0 ,0 ,0 ,1 ,1 ,1);
  set_matrix_row(matrix ,2 ,0 ,0 ,1 ,0 ,1 ,0 ,1 ,1);
  set_matrix_row(matrix ,3 ,0 ,0 ,0 ,1 ,1 ,1 ,1 ,0);
  return matrix;
}  
