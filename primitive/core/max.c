
#define _max() *++sp = (number)*(sp+1) < (number)*sp ? *sp : *(sp+1)

_primitive(pr_max) {
    _max();
    _next();
}
_define_primitive("MAX", pr_max);
