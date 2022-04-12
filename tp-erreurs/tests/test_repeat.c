#include <stdio.h>

#include "tests.h"
#include "../lib/repeat.h"

MU_TESTS_INIT


static int test_decode_three_bytes() {
  unsigned char bytes[3];

  bytes[0] = 0;
  bytes[1] = 0;
  bytes[2] = 0;
  mu_assert_eq("Decoding three bytes", decode_three_bytes(bytes), 0);

  bytes[0] = 0;
  bytes[1] = 0;
  bytes[2] = 1;
  mu_assert_eq("Decoding three bytes", decode_three_bytes(bytes), 0);

  bytes[0] = 1;
  bytes[1] = 0;
  bytes[2] = 0;
  mu_assert_eq("Decoding three bytes", decode_three_bytes(bytes), 0);
  
  bytes[0] = 0;
  bytes[1] = 1;
  bytes[2] = 0;
  mu_assert_eq("Decoding three bytes", decode_three_bytes(bytes), 0);

  bytes[0] = 1;
  bytes[1] = 1;
  bytes[2] = 0;
  mu_assert_eq("Decoding three bytes", decode_three_bytes(bytes), 1);

  bytes[0] = 128;
  bytes[1] = 0;
  bytes[2] = 0;
  mu_assert_eq("Decoding three bytes", decode_three_bytes(bytes), 0);
  
  bytes[0] = 0;
  bytes[1] = 128;
  bytes[2] = 128;
  mu_assert_eq("Decoding three bytes", decode_three_bytes(bytes), 128);

  bytes[0] = 1;
  bytes[1] = 2;
  bytes[2] = 6;
  mu_assert_eq("Decoding three bytes", decode_three_bytes(bytes), 2);

  bytes[0] = 0b10001001;        /* binary representation of 137 */
  bytes[1] = 0b10000000;        /* binary representation of 128 */
  bytes[2] = 0b00001000;        /* binary representation of   8 */
  mu_assert_eq("Decoding three bytes", decode_three_bytes(bytes), 0b10001000);
  /* binary representation of 136 */
  
  return 0;
}

static int all_tests() {
   mu_run_test(test_decode_three_bytes);
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
