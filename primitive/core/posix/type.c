#define _type()                                                   \
    do {                                                          \
        if ((long)*sp > 0)                                        \
            fwrite(_to_ptr(*(sp+1)), sizeof(char), *sp, stdout);  \
        sp += 2;                                                  \
    } while (0)

_primitive(pr_type) {
    _type();
    _next();
}

_define_primitive("TYPE", pr_type);
