#include <stdio.h>

#if VERBOSE

#define _debug(...) fprintf(stderr, __VA_ARGS__)

#define _print_stack()                 \
do {                                   \
    register cell *spx = sp0;          \
                                       \
   _debug("stack: ");                  \
                                       \
    while (sp < spx)                   \
        _debug("%lx ", (long)*--spx);  \
                                       \
    _debug("\n");                      \
} while(0)

#define _print_return_stack()          \
do {                                   \
    register cell *rpx = rp0;          \
                                       \
    _debug("return stack: ");          \
                                       \
    while (rp < rpx)                   \
        _debug("%lx ", (long)*--rpx);  \
                                       \
    _debug("\n");                      \
} while(0)

#else
#define _debug(...)
#define _print_stack()
#define _print_return_stack()
#endif
