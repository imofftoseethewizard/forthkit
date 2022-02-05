#define _primitive(name) if (0) name:
#define _execute(x)      (*--rp = _from_ptr(ip), ip = _to_ptr(x))

#define _next()                                 \
    do {                                        \
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

#define _dispatch() _next()
