#define _to_native_ptr(x)   ((cell *)(x))
#define _from_native_ptr(x) ((cell)(x))

#define _is_primitive(x)  ((void *)(x) >= &&__first && (void *)(x) <= &&__last)
#define _pr_addr(x) (&&x)
#define _pr_deref(x) x

#define _primitive(name)    if (0) name:
#define _execute(x)       (*--rp = _from_native_ptr(ip), ip = _to_native_ptr(x))

#define _next()                                                 \
    do {                                                        \
        while (ip && !_is_primitive(*ip)) _execute(*ip);        \
        if (ip) goto *_pr_deref(*ip++);                         \
        goto __last;                                            \
    }                                                           \
    while (0)

#define _dispatch() _next()
