
#define _dup() *--sp = *(sp+1)

_primitive(pr_dup) {
    _dup();
    _next();
}
_define_primitive("DUP", pr_dup);
