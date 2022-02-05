typedef void (native_word)(void);

#define _primitive(name) void name(void)

#define _to_native_ptr(x)   ((cell *)(x))
#define _from_native_ptr(x) ((cell)(x))

void first_primitive(void) {};

#define _is_primitive(x)  ((void *)(x) >= (void *)&first_primitive)
#define _execute(x)       (*--rp = _from_native_ptr(ip), ip = _to_native_ptr(x))

#define _next()

#define _dispatch()                                                                    \
    do {                                                                               \
        _debug("1 ip: %lx; sp: %lx\n", (cell)ip, (cell)sp);                            \
        while (ip && !_is_primitive(*ip)) {                                            \
            _debug("*ip: %lx\n", (cell)*ip);                                           \
            _execute(*ip);                                                             \
        }                                                                              \
        _debug("2 ip: %lx; *ip: %lx, sp: %lx\n", (cell)ip, ip?(cell)*ip:0, (cell)sp);  \
        if (ip) ((native_word *)(*ip++ + &first_primitive))(); \
    }                                                                                  \
    while (ip)

#define _pr_addr(x) (void *)(&x - &first_primitive)

auto void pr_store_compiled(void);
auto void pr_word(void);
