
#define _max() *++sp = *(sp+1) < *sp ? *sp : *(sp+1)

_primitive(pr_max) {
    _max();
    _next();
}
_define_primitive("MAX", pr_max);
