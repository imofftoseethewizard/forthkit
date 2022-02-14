
#define _min() *++sp = (number)*(sp+1) > (number)*sp ? *sp : *(sp+1)

_primitive(pr_min) {
    _min();
    _next();
}
_define_primitive("MIN", pr_min);
