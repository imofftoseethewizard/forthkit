divert(-1)
define(`__primitive', `divert(__primitive_implementations)    $1:')
define(`__end', `_next();
')
define(`__declare_primitives', `')

divert(__header_definitions)

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

define(`__implement_evaluator_core', `
__first:
    if (0) {
        undivert(__primitive_implementations)
    }
__last:

    _next();
')
divert`'dnl
