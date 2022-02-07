
#define _mod() *++sp = *(sp+1) % *sp

_primitive(pr_mod) {
    _mod();
    _next();
}
_define_primitive("%", pr_mod);
