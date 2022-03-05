/* The label `__first` must appear before any labels used as a target
   of the `next()` macro immediately below. That uses the `__first` and
   `__last` labels to distinguish primitives from compiled words.
*/
__first:

#define _primitive(name) if (0) name:
#define _execute(x)      (*--rp = _from_ptr(ip), ip = _to_ptr(x))
#define _pr_ref(x)       ((void *)&&x)
#define _pr_ref_base     (void *)&&__first
#define _pr_ref_limit    (void *)&&__last

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
        if (ip) goto *_pr_deref(*ip++);         \
                                                \
        _trace("exiting next: ");               \
        goto __last;                            \
    }                                           \
    while (0)

#define _dispatch()                             \
    _next();                                    \
__last:
