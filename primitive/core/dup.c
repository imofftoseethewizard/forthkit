
#define _dup() *--sp = *sp

_primitive(pr_dup) {
    _dup();
    _next();
}
define_primitive("DUP", pr_dup);
