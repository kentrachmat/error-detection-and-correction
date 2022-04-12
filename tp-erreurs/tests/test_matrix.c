#include <stdio.h>

#include "tests.h"
#include "../lib/binary_matrix.h"

MU_TESTS_INIT


static int test_zeromatrix() {
  binary_matrix z = zero_matrix(5, 10);
  int i, j;

  mu_assert("is zero", is_zero_matrix(z));
  mu_assert_eq("zero matrix: nb_columns", nb_columns(z), 10);
  mu_assert_eq("zero matrix: nb_rows", nb_rows(z), 5);
  
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 10; j++) {
      mu_assert_eq("Testing zero matrix", matrix_value(z, i, j), 0);
    }
  }
  return 0;
}

static int test_matrix_line1() {
  binary_matrix m = zero_matrix(3, 2);

  mu_assert("is_zero", is_zero_matrix(m));
  set_matrix_row(m, 2, 1, 0);
  mu_assert("is_zero", ! is_zero_matrix(m));

  
  /* Row 0 */
  mu_assert_eq("Testing value unset", matrix_value(m, 0, 0), 0);
  mu_assert_eq("Testing value unset", matrix_value(m, 0, 1), 0);
  /* Row 1 */
  mu_assert_eq("Testing value unset", matrix_value(m, 1, 0), 0);
  mu_assert_eq("Testing value unset", matrix_value(m, 1, 1), 0);
  /* Row 2 */
  mu_assert_eq("Testing value set", matrix_value(m, 2, 0), 1);
  mu_assert_eq("Testing value unset", matrix_value(m, 2, 1), 0);

  set_matrix_row(m, 0, 0, 1);
  /* Row 0 */
  mu_assert_eq("Testing value unset", matrix_value(m, 0, 0), 0);
  mu_assert_eq("Testing value set", matrix_value(m, 0, 1), 1);
  /* Row 1 */
  mu_assert_eq("Testing value unset", matrix_value(m, 1, 0), 0);
  mu_assert_eq("Testing value unset", matrix_value(m, 1, 1), 0);
  /* Row 2 */
  mu_assert_eq("Testing value set", matrix_value(m, 2, 0), 1);
  mu_assert_eq("Testing value unset", matrix_value(m, 2, 1), 0);

  return 0;
}

static int test_matrix_line2() {
  binary_matrix m = zero_matrix(5, 10);
  binary_matrix m2 = zero_matrix(5, 10);
  int i, j;

  mu_assert("equal matrices", equals_matrix(m, m2));
  set_matrix_row(m, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1);
  mu_assert("equal matrices", ! equals_matrix(m, m2));
  set_matrix_row(m2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1);
  mu_assert("equal matrices", equals_matrix(m, m2));
  
  for (i = 0; i < 5; i++) {
    if (i!=2)
      for (j = 0; j < 10; j++) {
        mu_assert_eq("Testing line", matrix_value(m, i, j), 0);
      }
  }
  mu_assert_eq("Testing 1", matrix_value(m, 2, 0), 1);
  mu_assert_eq("Testing 1", matrix_value(m, 2, 8), 1);
  mu_assert_eq("Testing 1", matrix_value(m, 2, 9), 1);
  for (j = 1; j < 8; j++) {
    mu_assert_eq("Testing line", matrix_value(m, 2, j), 0);
  }
  return 0;
}

static int test_matrix_multiplications() {
  binary_matrix m1 = zero_matrix(4, 3);
  binary_matrix m2 = zero_matrix(3, 2);
  binary_matrix m3;
  binary_matrix expected_result;
  binary_matrix copy;

  set_matrix_row(m1, 0, 1, 0, 1);
  set_matrix_row(m1, 1, 0, 1, 0);
  set_matrix_row(m1, 2, 0, 0, 0);
  set_matrix_row(m1, 3, 0, 0, 1);

  set_matrix_row(m2, 0, 1, 1);
  set_matrix_row(m2, 1, 0, 1);
  set_matrix_row(m2, 2, 1, 0);

  m3 = multiply_matrices(m1, m2);

  expected_result = zero_matrix(4, 2);
  set_matrix_row(expected_result, 0, 0, 1);
  set_matrix_row(expected_result, 1, 0, 1);
  set_matrix_row(expected_result, 2, 0, 0);
  set_matrix_row(expected_result, 3, 1, 0);

  mu_assert("Testing multiplication", equals_matrix(m3, expected_result));

  copy = copy_matrix(m3);
  mu_assert("Testing copy", equals_matrix(copy, m3));
  set_matrix_value(m3, 0, 0, 1);
  mu_assert("Testing equals", ! equals_matrix(m3, copy));

  return 0;
}

static int all_tests() {
   mu_run_test(test_zeromatrix);
   mu_run_test(test_matrix_line1);
   mu_run_test(test_matrix_line2);
   mu_run_test(test_matrix_multiplications);
   return mu_tests_success;
}
 
int main(int argc, char **argv) {
  int result = all_tests();
  if (result != 0) {
    fprintf(stderr, "TESTS FAILED!\n");
  }
  else {
    printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d (including %d assertions)\n", mu_tests_run, mu_assert_run);
  
  return result != 0;
}
