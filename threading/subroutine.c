#define _primitive(name)  void name(void)
#define _pr_value(x)        ((void *)&(x))
#define _pr_value_base      (void *)&engine
#define _pr_value_limit     __builtin_frame_address(0)

typedef void (native_word)(void);

#define _next()

#define _dispatch()                                     \
    do {                                                \
        _trace("start dispatch:     ");                 \
                                                        \
        while (ip && !_is_primitive(*ip)) {             \
            _trace("dispatch execute:   ");             \
            *--rp = _from_ptr(ip+1);                    \
            ip = _to_ptr(*ip);                          \
        }                                               \
                                                        \
        _trace("dispatch primitive: ");                 \
        if (ip) ((native_word *)(_to_pv(*ip++)))();  \
    }                                                   \
    while (ip);                                         \
                                                        \
    _trace("dispatch exited:   ");

#define _declare_primitive(x) auto void x(void)
_declare_primitive(pr_word);
_declare_primitive(pr_allot);
