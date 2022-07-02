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

#define _print_fiber_stack()                                             \
do {                                                                     \
    register cell *fpx = fp0;                                            \
                                                                         \
    _debug("fiber stack: ");                                             \
                                                                         \
    while (fp < fpx)                                                     \
        _debug("%d ", (int)*--fpx);                                      \
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
    _debug("s: %8lx, ip: %8lx; *ip: %8lx, *(ip+1): %8lx, rp: %8lx, *rp: %8lx, sp: %8lx, *sp: %8lx, dp: %8lx src: %.*s\n",  \
           steps, \
           _from_ptr(ip), ip?*ip:0, ip?*(ip+1):0,        \
           _from_ptr(rp), rp?*rp:0,                      \
           _from_ptr(sp), sp?*sp:0,                      \
           (long)_from_ptr(dp),                          \
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
#define _print_fiber_stack()
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
