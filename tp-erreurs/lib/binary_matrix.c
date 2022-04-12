#include <stdio.h>
#include <stdlib.h>

#include "binary_matrix.h"


binary_matrix zero_matrix(int rows, int columns) {
  binary_matrix matrix = malloc(sizeof(struct binary_matrix_s));
  int i;

  matrix->rows = rows;
  matrix->columns = columns;
  matrix->matrix = malloc(rows * sizeof(bitarray256_t *));

  for (i = 0; i < rows; i++) {
    matrix->matrix[i] = init_bitarray();
  }
  return matrix;
}

int is_zero_matrix(binary_matrix m) {
  int i, j;
  int zero = 1;
  for (i = 0; i < nb_rows(m) && zero; i++)
    for (j = 0; j < nb_columns(m) && zero; j++)
      zero = matrix_value(m, i, j) == 0;
  return zero;
}

int nb_columns(binary_matrix m) {
  return m->columns;
}

int nb_rows(binary_matrix m) {
  return m->rows;
}

void set_matrix_row(binary_matrix matrix, int row, ...) {
  va_list params;
  int i;

  va_start(params, row);

  for (i = 0; i < matrix->columns; i++) {
    int val = va_arg(params, int);
    if (val == 1)
      set_bit(matrix->matrix[row], i);
    else if (val != 0) {
      fprintf(stderr, "Value %d not allowed in binary matrix. Expecting 0 or 1\n", val);
      exit(2);
    }
  }

  va_end(params);
}

binary_matrix multiply_matrices(binary_matrix m1, binary_matrix m2) {
  binary_matrix result;
  int i, j, k;
  
  if (m1->columns != m2->rows) {
    fprintf(stderr, "The matrices can't be multiplied. Formats are incompatible.\n");
    exit(2);
  }

  result = zero_matrix(m1->rows, m2->columns);

  for (i = 0; i < m1->rows; i++) {
    for (k = 0; k < m2->columns; k++) {
      int sum = 0;
      for (j = 0; j < m1->columns; j++) {
        sum += matrix_value(m1, i, j) * matrix_value(m2, j, k);
      }
      set_matrix_value(result, i, k, sum % 2);
    }
  }
  return result;
}

int matrix_value(binary_matrix matrix, int i, int j) {
  return get_bit(matrix->matrix[i], j);
}

void set_matrix_value(binary_matrix matrix, int i, int j, int value) {
  if (value == 0) {
    unset_bit(matrix->matrix[i], j);
  } else if (value == 1) {
    set_bit(matrix->matrix[i], j);
  } else {
    fprintf(stderr, "Value %d not allowed in binary matrix. Expecing 0 or 1\n", value);
    exit(2);
  }
}

binary_matrix copy_matrix(binary_matrix matrix) {
  binary_matrix copy = zero_matrix(nb_rows(matrix), nb_columns(matrix));
  int i, j;

  for (i = 0; i < nb_rows(matrix); i++) {
    for (j = 0; j < nb_columns(matrix); j++) {
      set_matrix_value(copy, i, j, matrix_value(matrix, i, j));
    }
  }
  return copy;
}

int equals_matrix(binary_matrix matrix1, binary_matrix matrix2) {
  int result = 1;
  int i, j;
  result = nb_rows(matrix1) == nb_rows(matrix2) &&
    nb_columns(matrix1) == nb_columns(matrix2);
  for (i = 0; i < nb_rows(matrix1) && result; i++) {
    for (j = 0; j < nb_columns(matrix1) && result; j++) {
      result = (matrix_value(matrix1, i, j) == matrix_value(matrix2, i, j));
    }
  }
  return result;
}


void destroy_matrix(binary_matrix matrix) {
  int rows = nb_rows(matrix);
  int i;
  for (i = 0; i < rows; i++) {
    delete_bitarray(matrix->matrix[i]);
  }
  free(matrix->matrix);
}

void print_matrix(binary_matrix matrix) {
  int i, j;
  if (! matrix)
    printf("(NULL)\n");
  else {
    for (i = 0; i < nb_rows(matrix); i++) {
      for (j = 0; j < nb_columns(matrix); j++) {
        printf("%d ", matrix_value(matrix, i, j));
      }
      printf("\n");
    }
  }
}

binary_matrix pop_matrix_from_bitarray(bitarray256_t *bits, int n) {
  binary_matrix result = zero_matrix(1, n);
  int i;
  for (i = 0; i < n; i++) {
    set_matrix_value(result, 0, i, get_bit(bits, 0));
    right_shift_bit(bits, 1);
  }
  return result;
}

int append_matrix_to_bitarray(bitarray256_t *bits, binary_matrix matrix, int pos) {
  int nb_written = 0;
  int i;
  for (i = 0; i < nb_columns(matrix); i++) {
    if (matrix_value(matrix, 0, i))
      set_bit(bits, pos+i);
    nb_written++;
  }
  return nb_written;
}  
