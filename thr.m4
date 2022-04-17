include(`preamble.m4')dnl
define(`primitive', `divert(primitive_implementations)if (0) $1:')dnl
define(`declare_primitives', `')dnl

divert(header_definitions)dnl

#define _pr_value(x)       ((void *)&&x)
#define _pr_value_base     (void *)&&__first
#define _pr_value_limit    (void *)&&__last

#define _next()                                 \
    do {                                        \
        _trace("start next: ");                 \
                                                \
        while (ip && !_is_primitive(*ip)) {     \
            _trace("execute next: ");           \
            *--rp = _from_ptr(ip+1);            \
            ip = _to_ptr(*ip);                  \
        }                                       \
                                                \
        _trace("primitive next: ");             \
        if (ip) goto *_to_pv(*ip++);            \
                                                \
        _trace("exiting next: ");               \
        goto __last;                            \
    }                                           \
    while (0)

divert

define(`implement_evaluator_core', `
__first:
    undivert(primitive_implementations)
    _next();
__last:')dnl
