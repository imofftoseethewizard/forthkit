#define _pr_ref_base  (void *)&engine
#define _pr_ref_limit __builtin_frame_address(0)

typedef void (native_word)(void);

#define _primitive(name)  void name(void)
#define _execute(x)       (*--rp = _from_ptr(ip), ip = _to_ptr(x))
#define _pr_ref(x)        ((void *)&(x))

#define _next()

#define _dispatch()                                     \
    do {                                                \
        _trace("start dispatch:     ");                 \
                                                        \
        while (ip && !_is_primitive(*ip)) {             \
            _trace("dispatch execute:   ");             \
            _execute(*ip);                              \
        }                                               \
                                                        \
        _trace("dispatch primitive: ");                 \
        if (ip) ((native_word *)(_pr_deref(*ip++)))();  \
    }                                                   \
    while (ip);                                         \
                                                        \
    _trace("dispatch exited:   ");

/* These are referenced in premable.c and need a declaration. */
auto void pr_store_compiled(void);
auto void pr_word(void);
