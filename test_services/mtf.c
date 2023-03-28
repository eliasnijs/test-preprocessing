#include "mtf.h"

static int 
Mtf_run_multiple_tests(char *name, Mtf_Test tests[], int testc)
{
  int i, s, fcnt = 0;
  printf("  %s results (%s, %s): \n", name, __DATE__, __TIME__);
  for (i = 0; i < testc; ++i) {
    Mtf_Test *t = &tests[i];
    s = t->run();
    if (!s)
    {
      ++fcnt;
    }
    printf("%3d.  %-32s | %s\n",
        i,
        (s) ? "\033[38;2;210;255;000mSUCCESS\033[0m" :
              "\033[38;2;255;075;075mFAILED\033[0m",
        t->name);
  }
  printf("  tests finished: %d test(s) succeeded, %d test(s) failed\n", i-fcnt, fcnt);
  return(0);
}
