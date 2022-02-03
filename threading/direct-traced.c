#define _to_native_ptr(x)   ((cell *)(x))
#define _from_native_ptr(x) ((cell)(x))

    #define _is_primitive(x)  ((void *)(x) >= &&__first && (void *)(x) <= &&__last)
#define _execute(x)       (*--rp = _from_native_ptr(ip), ip = _to_native_ptr(x))

    #define _ref_engine_attr(x) &e[x]
    #define _fetch_addr(x) *((cell *)(x))
    #define _as_native_ptr(x) x

    #define _next()                                                                        \
        do {                                                                               \
            _debug("1 ip: %lx; sp: %lx\n", (cell)ip, (cell)sp);                            \
            print_stack(sp0, sp);\
            while (ip && !_is_primitive(*ip)) {                                            \
                _debug("*ip: %lx\n", (cell)*ip);                                           \
                _execute(*ip);                                      \
            }                                                                              \
            _debug("2 ip: %lx; *ip: %lx, sp: %lx\n", (cell)ip, ip?(cell)*ip:0, (cell)sp);  \
            if (ip) goto **ip++;                                                           \
            _debug("next 3: going to __last\n");                                           \
            goto __last;                                                                   \
        }                                                                                  \
        while (0)

    #define _pr_addr(x) (&&x)
