    #define c_pr_addr_flag (1L << (sizeof(cell) * 8 - 1))
    #define c_pr_addr_base ((size_t)&&__first - c_pr_addr_flag)

    #define _is_primitive(x)  (((size_t) x) & c_pr_addr_flag)
    #define _execute(x)       (*--rp = (cell *)ip, ip = (void **)(x))

    #define _ref_engine_attr(x) ((x) * sizeof(cell))
    #define _fetch_addr(x)      (cell)*((char *)e + (x))
    #define _as_native_ptr(x) (cell *)((char *)e + (cell)(x))

    #define _next()                                           \
        do {                                                  \
            while (ip && !_is_primitive(*ip)) _execute(*ip);  \
            if (ip) goto *(*ip++ + c_pr_addr_base);           \
            goto __last;                                      \
        }                                                     \
        while (0)

    #define _pr_addr(x) ((&&x) - c_pr_addr_base)
