    #define _primitive(name) if (0) name:
    #define _is_primitive(x)  ((x) >= &&__first && (x) <= &&__last)
    #define _execute(x)       (*--rp = (cell *)ip, ip = (void **)(x))

    #define _next()                                                                        \
        do {                                                                               \
            _debug("1 ip: %lx; sp: %lx\n", (cell)ip, (cell)sp);                            \
            while (ip && !_is_primitive(*ip)) {                                            \
                _debug("*ip: %lx\n", (cell)*ip);                                           \
                _execute(*ip);                                                             \
            }                                                                              \
            _debug("2 ip: %lx; *ip: %lx, sp: %lx\n", (cell)ip, ip?(cell)*ip:0, (cell)sp);  \
            if (ip) goto **ip++;                                                           \
            _debug("next 3: going to __last\n");                                           \
            goto __last;                                                                   \
        }                                                                                  \
        while (0)

    #define _pr_addr(x) (&&x)
    #define _dispatch() _next()
