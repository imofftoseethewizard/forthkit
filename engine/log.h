#include <stdio.h>

#if VERBOSE

#define _debug(...) fprintf(stderr, __VA_ARGS__)

#define _print_stack()                                                   \
do {                                                                     \
    register cell *spx = sp0;                                            \
                                                                         \
   _debug("stack: ");                                                    \
                                                                         \
    while (sp < spx)                                                     \
        _debug("%lx ", (long)*--spx);                                    \
                                                                         \
    _debug("\n");                                                        \
} while(0)

#define _print_return_stack()                                            \
do {                                                                     \
    register cell *rpx = rp0;                                            \
                                                                         \
    _debug("return stack: ");                                            \
                                                                         \
    while (rp < rpx)                                                     \
        _debug("%lx ", (long)*--rpx);                                    \
                                                                         \
    _debug("\n");                                                        \
} while(0)

#define _print_registers()                                               \
do {                                                                     \
    _debug("ip: %lx; *ip: %lx, rp: %lx, *rp: %lx, sp: %lx, *sp: %lx\n",  \
           (cell)ip, ip?(cell)*ip:0,                                     \
           (cell)rp, rp?(cell)*rp:0,                                     \
           (cell)sp, sp?(cell)*sp:0);                                    \
} while (0)


#else
#define _debug(...)
#define _print_stack()
#define _print_return_stack()
#define _print_registers()
#endif

#if TRACE

#define _trace(label)                                                    \
    do {                                                                 \
    _debug(label);                                                       \
    _print_registers();                                                  \
} while(0)

#else

#define _trace(label)

#endif
