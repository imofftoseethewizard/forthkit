    #define _is_primitive(x)  ((void *)(x) >= &&__first && (void *)(x) <= &&__last)
    #define _execute(x)       (*--rp = ip, ip = (cell *)(x))

    #define _ref_engine_attr(x) &e[x]
    #define _fetch_addr(x) *((cell *)(x))
    #define _as_native_ptr(x) x

    #define _next()                                           \
        do {                                                  \
            while (ip && !_is_primitive(*ip)) _execute(*ip);  \
            if (ip) goto **ip++;                              \
            goto __last;                                      \
        }                                                     \
        while (0)

    #define _pr_addr(x) (&&x)
