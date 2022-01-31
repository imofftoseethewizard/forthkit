
#define _mod() *++sp = *(sp+1) % *sp

_primitive(pr_mod) {
    _mod();
    _next();
}
define_primitive("%", pr_mod);
