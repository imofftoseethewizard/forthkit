/* The label `__first` must appear before any labels used as a target
   of the `next()` macro immediately below. That uses the `__first` and
   `__last` labels to distinguish primitives from compiled words.
*/
__first:

#define _primitive(name) if (0) name:
#define _execute(x)      (*--rp = _from_ptr(ip), ip = _to_ptr(x))
#define _pr_ref(x)       ((void *)&&x)

#define _next()                                 \
    do {                                        \
_debug("c_pr_addr_base: %lx\n", c_pr_addr_base); \
        _trace("start next:     ");             \
                                                \
        while (ip && !_is_primitive(*ip)) {     \
            _trace("next execute:   ");         \
            _execute(*ip);                      \
        }                                       \
                                                \
        _trace("next primitive: ");             \
        if (ip) goto *_pr_deref(*ip++);         \
                                                \
        _trace("next exiting:   ");             \
        goto __last;                            \
    }                                           \
    while (0)

#define _dispatch() \
    _next();        \
__last:
