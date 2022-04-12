#include <stdio.h>

#include "tests.h"
#include "../lib/linear_coding.h"
#include "../lib/generator_matrices.h"

MU_TESTS_INIT

static int test_code_word_parity(){
  binary_matrix g = parity_generator(2);
  binary_matrix word, encoded;
  int i;
  /* Words that will be encoded */
  int u0[] = {0, 0},
    u1[] = {0, 1},
    u2[] = {1, 0},
    u3[] = {1, 1};
  /* Expected encoding */
  int v0[] = {0, 0, 0},
    v1[] = {0, 1, 1},
    v2[] = {1, 0, 1},
    v3[] = {1, 1, 0};

  /* u0 */
  word = zero_matrix(1, 2);
  for (i = 0; i < 2; i++)
    set_matrix_value(word, 0, i, u0[i]);
  encoded = code_word(word, g);
  mu_assert_eq("Encoding u0", matrix_value(encoded, 0, 0), v0[0]);
  mu_assert_eq("Encoding u0", matrix_value(encoded, 0, 1), v0[1]);
  mu_assert_eq("Encoding u0", matrix_value(encoded, 0, 2), v0[2]);
  destroy_matrix(word);
  destroy_matrix(encoded);
  
  /* u1 */
  word = zero_matrix(1, 2);
  for (i = 0; i < 2; i++)
    set_matrix_value(word, 0, i, u1[i]);
  encoded = code_word(word, g);
  mu_assert_eq("Encoding u1", matrix_value(encoded, 0, 0), v1[0]);
  mu_assert_eq("Encoding u1", matrix_value(encoded, 0, 1), v1[1]);
  mu_assert_eq("Encoding u1", matrix_value(encoded, 0, 2), v1[2]);
  destroy_matrix(word);
  destroy_matrix(encoded);
  
  /* u2 */ 
  word = zero_matrix(1, 2);
  for (i = 0; i < 2; i++)
    set_matrix_value(word, 0, i, u2[i]);
  encoded = code_word(word, g);
  mu_assert_eq("Encoding u2", matrix_value(encoded, 0, 0), v2[0]);
  mu_assert_eq("Encoding u2", matrix_value(encoded, 0, 1), v2[1]);
  mu_assert_eq("Encoding u2", matrix_value(encoded, 0, 2), v2[2]);
  destroy_matrix(word);
  destroy_matrix(encoded);

  /* u3 */
  word = zero_matrix(1, 2);
  for (i = 0; i < 2; i++)
    set_matrix_value(word, 0, i, u3[i]);
  encoded = code_word(word, g);
  mu_assert_eq("Encoding u3", matrix_value(encoded, 0, 0), v3[0]);
  mu_assert_eq("Encoding u3", matrix_value(encoded, 0, 1), v3[1]);
  mu_assert_eq("Encoding u3", matrix_value(encoded, 0, 2), v3[2]);
  destroy_matrix(word);
  destroy_matrix(encoded);

  return 0;
}

static int test_transposed_control_matrix() {
  binary_matrix g = zero_matrix(3, 7);
  binary_matrix tH;
  int column0[] = {1, 0, 1, 1, 0, 0, 0};
  int column1[] = {0, 1, 0, 0, 1, 0, 0};
  int column2[] = {1, 0, 0, 0, 0, 1, 0};
  int column3[] = {1, 0, 1, 0, 0, 0, 1};
  int i;

  set_matrix_row(g, 0, 1, 0, 0, 1, 0, 1, 1);
  set_matrix_row(g, 1, 0, 1, 0, 0, 1, 0, 0);
  set_matrix_row(g, 2, 0, 0, 1, 1, 0, 0, 1);

  tH = transposed_control_matrix(g);

  mu_assert_eq("transposed control", nb_rows(tH), 7);
  mu_assert_eq("transposed control", nb_columns(tH), 4);

  for (i = 0; i < nb_rows(tH); i++) {
    mu_assert_eq("transposed control", matrix_value(tH, i, 0), column0[i]);
    mu_assert_eq("transposed control", matrix_value(tH, i, 1), column1[i]);
    mu_assert_eq("transposed control", matrix_value(tH, i, 2), column2[i]);
    mu_assert_eq("transposed control", matrix_value(tH, i, 3), column3[i]);
  }
  
  return 0;
}

static int test_syndrome() {
  binary_matrix g = repeat3_generator(2);
  binary_matrix tH = transposed_control_matrix(g);
  binary_matrix w = zero_matrix(1, 2);
  binary_matrix result, result_orig, s, corrected;

  result = code_word(w, g);

  mu_assert("0*g == 0", is_zero_matrix(result));

  s = syndrome(result, tH);

  mu_assert("syndrome should be 0", is_zero_matrix(s));

  set_matrix_row(w, 0, 0, 1);
  result = code_word(w, g);
  s = syndrome(result, tH);
  mu_assert("syndrome should be 0", is_zero_matrix(s));
 
  result_orig = copy_matrix(result);
  set_matrix_value(result, 0, 2, 1);
  /* result should now be (0 1 1 1 0 1) */

  s = syndrome(result, tH);
  mu_assert("syndrome should not be 0", ! is_zero_matrix(s));
  mu_assert_eq("syndrome should be (1 0 0 0)", matrix_value(s, 0, 0), 1);
  mu_assert_eq("syndrome should be (1 0 0 0)", matrix_value(s, 0, 1), 0);
  mu_assert_eq("syndrome should be (1 0 0 0)", matrix_value(s, 0, 2), 0);
  mu_assert_eq("syndrome should be (1 0 0 0)", matrix_value(s, 0, 3), 0);

  corrected = correct_result(result, s, tH);
  mu_assert("Check correction", equals_matrix(result_orig, corrected));

  result = copy_matrix(corrected);
  set_matrix_value(result, 0, 5, 0);
  s = syndrome(result, tH);
  mu_assert("syndrome should not be 0", ! is_zero_matrix(s));
  corrected = correct_result(result, s, tH);
  mu_assert("Check correction", equals_matrix(result_orig, corrected));
  
  s = syndrome(result_orig, tH); 
  corrected = correct_result(result_orig, s, tH);
  mu_assert("Check correction", corrected == NULL);
  
  return 0; 
}

static int test_encoding() {
  binary_matrix g = parity_generator(4);
  buffer_t read, write;
  int expected_bits[] = {0, 1, 0, 0, 1,
      0, 0, 0, 1, 1,
      1, 1, 0, 0, 0,
      0, 0, 0, 0, 0};
  int i;
  char message[200];
  
  read.bits = init_bitarray();
  read.size = 0;
  write.bits = init_bitarray();
  write.size = 0;

  add_byte(read.bits, 0, 65);
  read.size += 8;
  add_byte(read.bits, 8, 192);
  read.size += 8;

  encode_with_buffer(&read, &write, g);
  
  for (i = 0; i < 20; i++) {
    sprintf(message, "Testing value of bit %d", i);
    mu_assert_eq(message, get_bit(write.bits, i), expected_bits[i]);
  }
  return 0;
}

static int test_decode_word() {
  binary_matrix g = repeat3_generator(2);
  binary_matrix tH = transposed_control_matrix(g);
  binary_matrix w = zero_matrix(1, 2);
  binary_matrix result, decoded;

  set_matrix_row(w, 0, 0, 1);
  /* w is (0 1) */
  
  result = code_word(w, g);
  decoded = decode_word(result, tH);

  mu_assert_eq("test decoded size", nb_columns(decoded), 2);
  mu_assert_eq("test decoded value", matrix_value(decoded, 0, 0), 0);
  mu_assert_eq("test decoded value", matrix_value(decoded, 0, 1), 1);
  
  set_matrix_value(result, 0, 2, 1);
  /* result should now be (0 1 1 1 0 1) */

  decoded = decode_word(result, tH);

  mu_assert_eq("test decoded size", nb_columns(decoded), 2);
  mu_assert_eq("test decoded value", matrix_value(decoded, 0, 0), 0);
  mu_assert_eq("test decoded value", matrix_value(decoded, 0, 1), 1);

  set_matrix_value(result, 0, 0, 1);
  /* result should now be (1 1 1 1 0 1) */

  decoded = decode_word(result, tH);

  mu_assert_eq("test decoded size", nb_columns(decoded), 2);
  mu_assert_eq("test decoded value", matrix_value(decoded, 0, 0), 1);
  mu_assert_eq("test decoded value", matrix_value(decoded, 0, 1), 1);
  

  return 0;
} 

static int all_tests() { 
  mu_run_test(test_code_word_parity);
  mu_run_test(test_transposed_control_matrix);
  mu_run_test(test_syndrome);
  mu_run_test(test_encoding);
  mu_run_test(test_decode_word);
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
