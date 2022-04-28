#include <stdio.h>

#if VERBOSE

#define _info(...) fprintf(stderr, __VA_ARGS__)
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
    _debug("ip: %16lx; *ip: %16lx, rp: %16lx, *rp: %16lx, sp: %16lx, *sp: %16lx, here: %16lx\n",  \
           (long)ip, ip?(long)*ip:0,                                     \
           (long)rp, rp?(long)_to_ptr(*rp):0,                           \
           (long)sp, sp?(long)*sp:0,                                    \
           (long)here);                                    \
} while (0)


#else

#if LOG
#define _info(...) fprintf(stderr, __VA_ARGS__)
#else
#define _info(...)
#endif

#define _debug(...)
#define _print_stack()
#define _print_return_stack()
#define _print_registers()
#endif

#if TRACE

#define _trace(label)                                                    \
    do {                                                                 \
        _debug("%40s", label);                                          \
        _print_registers();                                             \
    } while(0)

#else

#define _trace(label)

#endif
