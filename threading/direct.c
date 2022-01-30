    #define _is_primitive(x)  ((x) >= &&__first && (x) <= &&__last)
    #define _execute(x)       (*--rp = (cell *)ip, ip = (void **)(x))

    #define _next()                                           \
        do {                                                  \
            while (ip && !_is_primitive(*ip)) _execute(*ip);  \
            if (ip) goto **ip++;                              \
            goto __last;                                      \
        }                                                     \
        while (0)

    #define _pr_addr(x) (&&x)
