#if CELL_SIZE == 2
    #define _print_registers()                                               \
        do {                                                                     \
            _debug("s: %4x, ip: %4x; *ip: %4x, *(ip+1): %4x, wp: %4x; *wp: %4x, rp: %4x, *rp: %4x, sp: %4x, *sp: %4x, dp: %4x src: %.*s\n",  \
                   steps, \
                   _from_ptr(ip), ip?*ip:0, ip?*(ip+1):0,        \
                   _from_ptr(wp), wp?*wp:0,                                                                                                    \
                   _from_ptr(rp), rp?*rp:0,                      \
                   _from_ptr(sp), sp?*sp:0,                      \
                   _from_ptr(dp),                          \
                   e[ea_source_len]-e[ea_source_idx], \
                   (char *)_to_ptr(e[ea_source_addr]) + e[ea_source_idx]);      \
        } while (0)

#elif CELL_SIZE == 4
    #define _print_registers()                                               \
        do {                                                                     \
            _debug("s: %8x, ip: %8x; *ip: %8x, *(ip+1): %8x, wp: %8x; *wp: %8x, rp: %8x, *rp: %8x, sp: %8x, *sp: %8x, dp: %8x src: %.*s\n",  \
                   steps, \
                   _from_ptr(ip), ip?*ip:0, ip?*(ip+1):0,        \
                   _from_ptr(wp), wp?*wp:0,                                                                                                    \
                   _from_ptr(rp), rp?*rp:0,                      \
                   _from_ptr(sp), sp?*sp:0,                      \
                   _from_ptr(dp),                          \
                   e[ea_source_len]-e[ea_source_idx], \
                   (char *)_to_ptr(e[ea_source_addr]) + e[ea_source_idx]);      \
        } while (0)

#else // CELL_SIZE != 8
    #define _print_registers()                                               \
        do {                                                                     \
            _debug("s: %8x, ip: %8x; *ip: %8x, *(ip+1): %8x, wp: %8x; *wp: %8x, rp: %8x, *rp: %8x, sp: %8x, *sp: %8x, dp: %8x src: %.*s\n",  \
                   steps, \
                   _from_ptr(ip), ip?*ip:0, ip?*(ip+1):0,        \
                   _from_ptr(wp), wp?*wp:0,                      \
                   _from_ptr(rp), rp?*rp:0,                      \
                   _from_ptr(sp), sp?*sp:0,                      \
                   _from_ptr(dp),                          \
                   e[ea_source_len]-e[ea_source_idx], \
                   (char *)_to_ptr(e[ea_source_addr]) + e[ea_source_idx]);      \
        } while (0)

#endif

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
