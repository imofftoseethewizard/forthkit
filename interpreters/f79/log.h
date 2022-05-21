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
    _debug("s: %8x, ip: %8x; *ip: %8x, *(ip+1): %8x, rp: %8x, *rp: %8x, sp: %8x, *sp: %8x, dp: %8x src: %.*s\n",  \
           steps, \
           _from_ptr(ip), ip?*ip:0, ip?*(ip+1):0,        \
           _from_ptr(rp), rp?*rp:0,                      \
           _from_ptr(sp), sp?*sp:0,                      \
           _from_ptr(dp),                                      \
           e[ea_source_len]-e[ea_source_idx], \
           (char *)_to_ptr(e[ea_source_addr]) + e[ea_source_idx]);      \
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
