#define _is_primitive(x)  ((void*)(x) < (void *)e || (void *)(x) >= (void *)e + sizeof(e))
#define _execute(x)       (*--rp = (cell *)ip, ip = (void **)(x))
#define _primitive(name)  void name(void)

#define _next()

#define _dispatch()                                                                    \
    do {                                                                               \
        _debug("1 ip: %lx; sp: %lx\n", (cell)ip, (cell)sp);                            \
        while (ip && !_is_primitive(*ip)) {                                            \
            _debug("*ip: %lx\n", (cell)*ip);                                           \
            _execute(*ip);                                                             \
        }                                                                              \
        _debug("2 ip: %lx; *ip: %lx, sp: %lx\n", (cell)ip, ip?(cell)*ip:0, (cell)sp);  \
        if (ip) (*(native_word *)ip++)();                                              \
    }                                                                                  \
    while (ip)

#define _pr_addr(x) (&x)
