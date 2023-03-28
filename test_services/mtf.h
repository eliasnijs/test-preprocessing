#ifndef _LIBMTF_
#define _LIBMTF_

#include <stdio.h>

#define Mtf_T(a) {#a, a}
#define Mtf_RunMultipleTests(a) \
  Mtf_run_multiple_tests(#a, a, sizeof(a)/sizeof(*(a)));

typedef struct Mtf_Test {
  char *name;
  int (* run)(void);
} Mtf_Test;

static int
Mtf_run_multiple_tests(char *name, Mtf_Test tests[], int testc);

#endif
