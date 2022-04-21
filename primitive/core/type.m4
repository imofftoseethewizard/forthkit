#define _type()                                                   \
    do {                                                          \
        if ((long)*sp > 0)                                        \
            fwrite(_to_ptr(*(sp+1)), sizeof(char), *sp, stdout);  \
        sp += 2;                                                  \
    } while (0)

__primitive(pr_type)  
{
    _type();
}
__end
__define_primitive("TYPE", pr_type);
