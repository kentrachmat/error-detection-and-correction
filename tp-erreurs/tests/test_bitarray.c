#include <stdio.h>

#include "tests.h"
#include "../lib/bitarray.h"

MU_TESTS_INIT


static int test_bitarray_init() {
  bitarray256_t *bits = init_bitarray();

  mu_assert("bitarray not correctly initialised", bits->size == 0);
  mu_assert("bitarray not correctly initialised", bits->data[0] == bits->data[1]);
  mu_assert("bitarray not correctly initialised", bits->data[1] == bits->data[2]);
  mu_assert("bitarray not correctly initialised", bits->data[2] == bits->data[3]);
  mu_assert("bitarray not correctly initialised", bits->data[3] == 0);
  delete_bitarray(bits);
  return 0;
}

static int test_bitarray_access() {
  bitarray256_t *bits = init_bitarray();
  char message[200];

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    sprintf(message, "get should be 0 (i=%d)", i);
    mu_assert(message, get_bit(bits, i) == 0);
  }

  set_bit(bits, 0);
  mu_assert("get should be 1", get_bit(bits, 0) == 1);
  for (int i = 1; i < ALPHABET_SIZE; i++) {
    sprintf(message, "get should be 0 (i=%d)", i);
    mu_assert(message, get_bit(bits, i) == 0);
  }

  unset_bit(bits, 0);
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    sprintf(message, "get should be 0 (i=%d)", i);
    mu_assert(message, get_bit(bits, i) == 0);
  }

  set_bit(bits, 63);
  mu_assert("get should be 1", get_bit(bits, 63) == 1);
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (i!=63) {
      sprintf(message, "get should be 0 (i=%d)", i);
      mu_assert(message, get_bit(bits, i) == 0);
    }
  }
  unset_bit(bits, 63);
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    sprintf(message, "get should be 0 (i=%d)", i);
    mu_assert(message, get_bit(bits, i) == 0);
  }

  set_bit(bits, 64);
  mu_assert("get should be 1", get_bit(bits, 64) == 1);
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (i!=64) {
      sprintf(message, "get should be 0 (i=%d)", i);
      mu_assert(message, get_bit(bits, i) == 0);
    }
  }
  set_bit(bits, 64);
  mu_assert("get should be 1", get_bit(bits, 64) == 1);
  mu_assert("size should be 64", bits->size == 65);
  
  delete_bitarray(bits);
  return 0;
}

static int test_bitarray_get_bits() {
  bitarray256_t *bits = init_bitarray();

  mu_assert("we should have 0", get_bits(bits, 10, 20) == 0);
  mu_assert("we should have 0", get_bits(bits, 60, 20) == 0);

  set_bit(bits, 60);

  mu_assert_eq("test", get_bit(bits, 60), 1);
  mu_assert_eq("we should have 1", get_bits(bits, 60, 1), 1);
  mu_assert_eq("we should have 1", get_bits(bits, 60, 2), 1);
  mu_assert_eq("we should have 1", get_bits(bits, 60, 3), 1);
  mu_assert_eq("we should have 1", get_bits(bits, 60, 4), 1);
  
  mu_assert_eq("we should have 2", get_bits(bits, 59, 2), 2);
  mu_assert_eq("we should have 4", get_bits(bits, 58, 3), 4);
  mu_assert_eq("we should have 8", get_bits(bits, 57, 4), 8);

  set_bit(bits, 64);
  mu_assert_eq("get_bits", get_bits(bits, 59, 5), 2); /*   00010 */
  mu_assert_eq("get_bits", get_bits(bits, 59, 6), 34); /* 100010 */

  unset_bit(bits, 64);
  set_bit(bits, 65);
  set_bit(bits, 67);

  mu_assert_eq("get_bits", get_bits(bits, 60, 8), 0b10100001); 
  mu_assert_eq("get_bits", get_bits(bits, 60, 7), 0b0100001); 
  mu_assert_eq("get_bits", get_bits(bits, 64, 8), 0b00001010);

  set_bit(bits, 255);
  set_bit(bits, 250);
  mu_assert_eq("get_bits", get_bits(bits, 249, 7), 0b1000010);
  
  delete_bitarray(bits);
  return 0;
}

static int test_bitarray_shift() {
  bitarray256_t *bits = init_bitarray();
  char message[200];

  set_bit(bits, 63);
  set_bit(bits, 64);
  set_bit(bits, 127);
  mu_assert("Bit at position 63 should be one", get_bit(bits, 63) == 1);
  mu_assert("Bit at position 64 should be one", get_bit(bits, 64) == 1);
  mu_assert("Bit at position 127 should be one", get_bit(bits, 127) == 1);
  mu_assert("Size should be 128", bits->size == 128);

  left_shift_bit(bits);
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (i!=64 && i != 65 && i != 128) {
      sprintf(message, "Bit should be 0 (i=%d)", i);
      mu_assert(message, get_bit(bits, i) == 0);
    } else {
      sprintf(message, "Bit should be 1 (i=%d)", i);
      mu_assert(message, get_bit(bits, i) == 1);
    }
  }

  set_bit(bits, 255);
  mu_assert("Bit at position 255 should be one", get_bit(bits, 255) == 1);
  mu_assert("Size should be ALPHABET_SIZE", bits->size == ALPHABET_SIZE);
  left_shift_bit(bits);
  mu_assert("Size should still be ALPHABET_SIZE", bits->size == ALPHABET_SIZE);
  mu_assert("Bit at position 0 should be zero", get_bit(bits, 0) == 0);
  mu_assert("Bit at position 255 should be zero", get_bit(bits, 255) == 0);

  delete_bitarray(bits);
  return 0;
}

static int test_bitarray_shift_right() {
  bitarray256_t *bits = init_bitarray();

  set_bit(bits, 0);
  set_bit(bits, 63);
  set_bit(bits, 64);
  set_bit(bits, 127);

  right_shift_bit(bits, 1);
  mu_assert_eq("Bit at position 0 should be one", get_bit(bits, 0), 0);
  mu_assert_eq("Bit at position 62 should be one", get_bit(bits, 62), 1);
  mu_assert_eq("Bit at position 63 should be one", get_bit(bits, 63), 1);
  mu_assert_eq("Bit at position 126 should be one", get_bit(bits, 126), 1);
  mu_assert_eq("Size should be 127", bits->size, 127);

  right_shift_bit(bits, 7);
  mu_assert_eq("Bit at position 55 should be one", get_bit(bits, 55), 1);
  mu_assert_eq("Bit at position 56 should be one", get_bit(bits, 56), 1);
  mu_assert_eq("Bit at position 119 should be one", get_bit(bits, 119), 1);
  mu_assert_eq("Size should be 120", bits->size, 120);

  right_shift_bit(bits, 50);
  mu_assert_eq("Bit at position 5 should be one", get_bit(bits, 5), 1);
  mu_assert_eq("Bit at position 6 should be one", get_bit(bits, 6), 1);
  mu_assert_eq("Bit at position 69 should be one", get_bit(bits, 69), 1);
  mu_assert_eq("Size should be 70", bits->size, 70);

  int b = pop_byte(bits);
  mu_assert_eq("Byte should be 6", b, 6);
  mu_assert_eq("Size should be 62", bits->size, 62);
  mu_assert_eq("Bit at position 61 should be one", get_bit(bits, 61), 1);
  mu_assert_eq("Byte should be 0", pop_byte(bits), 0);
  
  
  return 0;
}

static int all_tests() {
   mu_run_test(test_bitarray_init);
   mu_run_test(test_bitarray_access);
   mu_run_test(test_bitarray_get_bits);
   mu_run_test(test_bitarray_shift);
   mu_run_test(test_bitarray_shift_right);
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
