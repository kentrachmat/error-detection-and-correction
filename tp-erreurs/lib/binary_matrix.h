#ifndef BINARY_MATRIX_H
#define BINARY_MATRIX_H

#include <stdarg.h>
#include "bitarray.h"

typedef struct binary_matrix_s {
  bitarray256_t **matrix;
  int rows;
  int columns;
} * binary_matrix;

/**
 * Produce a matrix containing only zeroes with the given number of rows and
 * columns.
 *
 * @param rows: number of rows in the matrix
 * @param columns: number of columns in the matrix
 * @return the binary matrix
 */
binary_matrix zero_matrix(int rows, int columns);

/**
 * Determines if a matrix only contains zeroes.
 *
 * @return a value different from 0 iff the matrix is a zero matrix (ie. a
 * matrix for which all values are zero), otherwise returns 0.
 */
int is_zero_matrix(binary_matrix);

/**
 * Number of columns in the matrix.
 *
 * @return the number of columns in the matrix
 * @complexity O(1)
 */
int nb_columns(binary_matrix);

/**
 * Number of rows in the matrix.
 *
 * @return the number of rows in the matrix
 * @complexity O(1)
 */
int nb_rows(binary_matrix);

/**
 * Sets the row of a matrix.
 * 
 * You can see an example in the file ../tests/test_matrix.c in the function test_matrix_line1
 * @param matrix: the matrix to modify
 * @param row: the number of the row to set (the first one is row 0).
 * @param ...: the following parameters are the values of the corresponding row.
 *             there must be as many values as columns in the row.
 */
void set_matrix_row(binary_matrix matrix, int row, ...);

/**
 * Multiply matrix m1 by matrix m2
 *
 * @return a binary_matrix with one row containing the result of the multiplication.
 */
binary_matrix multiply_matrices(binary_matrix m1, binary_matrix m2);
  

/**
 * Get the value at coordinates (i, j) in the matrix.
 *
 * @param i: row number (starting at 0)
 * @param j: column number (starting at 0)
 * @return the value of the matrix at that position
 */
int matrix_value(binary_matrix matrix, int i, int j);

/**
 * Sets the value in the matrix at the specified coordinates.
 *
 * @param i: row number (starting at 0)
 * @param j: column number (starting at 0)
 * @param value: the value of the matrix at that position (either 0 or 1)
 * @post matrix_value(matrix, i, j) == value
 */
void set_matrix_value(binary_matrix matrix, int i, int j, int value);

/**
 * Copy a matrix
 *
 * @param matrix: the matrix to be copied
 * @return a copy of the matrix.
 */
binary_matrix copy_matrix(binary_matrix matrix);

/**
 * Determines if two matrices are equals.
 *
 * @returns a value different from 0 iff the two matrices in parameter are equals
 */
int equals_matrix(binary_matrix matrix1, binary_matrix matrix2);

/**
 * Destroy the matrix given in parameter.
 */ 
void destroy_matrix(binary_matrix matrix);

/**
 * Print the matrix given in parameter.
 */ 
void print_matrix(binary_matrix matrix);

/**
 * @return a matrix of size 1*n taken from the first bits of the bit array.
 * @post the first n bits of the bit array have been discarded (left shift)
 */
binary_matrix pop_matrix_from_bitarray(bitarray256_t *bits, int n);


/**
 * Put the bits in the matrix within the bitarray at the specified position.
 *
 * @param bits: a bitarray
 * @param matrix: a binary matrix, with one row
 * @param pos: starting position in the bitarray where the bits should be set
 */
int append_matrix_to_bitarray(bitarray256_t *bits, binary_matrix matrix, int pos);

#endif
