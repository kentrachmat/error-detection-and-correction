 /* http://www.jera.com/techinfo/jtns/jtn002.html */
#include <stdio.h>
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define mu_assert_msg(message, message2, test) do { mu_assert_run++; if (!(test)) {fprintf(stderr,"%s%s (%s:%d)\n",message,message2,__FILE__,__LINE__); return 1;} } while (0)
#define mu_assert(message, test) mu_assert_msg(message, "", test)
#define mu_assert_eq(message, a, b) do { char msg[500]; sprintf(msg, " ("STR(a)" != "STR(b)" -- "STR(a)"==%d and "STR(b)"==%d)",a, b); mu_assert_msg(message, msg, (a)==(b)); } while(0)
#define mu_run_test(test) do { mu_tests_success |= test(); mu_tests_run++; } while (0)
#define MU_TESTS_INIT int mu_tests_run = 0; int mu_assert_run = 0; int mu_tests_success = 0;

extern int mu_tests_run;
extern int mu_assert_run;
extern int mu_tests_success;
