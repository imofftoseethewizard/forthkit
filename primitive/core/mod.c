#define _mod() *++sp = (number)*(sp+1) % (number)*sp

_primitive(pr_mod) {
    _mod();
    _next();
}
_define_primitive("%", pr_mod);
