    #define _primitive(name) if (0) name:
#define _to_native_ptr(x)   (cell *)((char *)e + (x))
#define _from_native_ptr(x) (cell)((char *)(x) - (char *)e)

    #define c_pr_addr_flag (1L << (sizeof(cell) * 8 - 1))
    #define c_pr_addr_base ((size_t)&&__first - c_pr_addr_flag)

    #define _is_primitive(x)  (((size_t) x) & c_pr_addr_flag)
#define _execute(x)       (*--rp = _from_native_ptr(ip), ip = _to_native_ptr(x))

    #define _ref_engine_attr(x) ((x) * sizeof(cell))
    #define _fetch_addr(x)      (cell)*((char *)e + (x))
    #define _as_native_ptr(x) (cell *)((char *)e + (cell)(x))

    #define _next()                                                                        \
        do {                                                                               \
            _debug("1 ip: %lx; sp: %lx\n", (long)ip, (long)sp);                            \
            while (ip && !_is_primitive(*ip)) {                                            \
                _debug("*ip: %lx\n", (long)*ip);                                           \
                _execute(*ip);                                                             \
                print_return_stack(rp0, rp); \
            }                                                                              \
            _debug("2 ip: %lx; *ip: %lx, sp: %lx\n", (long)ip, ip?(long)*ip:0, (long)sp);  \
            if (ip) goto *(*ip++ + c_pr_addr_base);                                        \
            _debug("next 3: going to __last\n");                                           \
            goto __last;                                                                   \
        }                                                                                  \
        while (0)

    #define _dispatch() _next()
    #define _pr_addr(x) ((&&x) - c_pr_addr_base)
