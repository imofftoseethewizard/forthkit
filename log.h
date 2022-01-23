#include <stdio.h>

#if VERBOSE
#define _debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define _debug(x)
#endif
