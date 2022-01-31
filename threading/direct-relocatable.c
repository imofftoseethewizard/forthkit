    #define _primitive(name) if (0) name:
    #define c_primitive_addr (1L << (sizeof(cell) * 8 - 1))
    register size_t primitive_base = (size_t)&&__first - c_primitive_addr;

    #define _is_primitive(x)  (((size_t) x) & c_primitive_addr)
    #define _execute(x)       (*--rp = (cell *)ip, ip = (void **)(x))

    #define _next()                                           \
        do {                                                  \
            while (ip && !_is_primitive(*ip)) _execute(*ip);  \
            if (ip) goto *(*ip++ + primitive_base);           \
            goto __last;                                      \
        }                                                     \
        while (0)

    #define _pr_addr(x) ((&&x) - primitive_base)
    #define _dispatch() _next()
