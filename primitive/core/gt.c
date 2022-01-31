
#define _gt() *++sp = *(sp+1) >  *sp

_primitive(pr_gt) {
    _gt();
    _next();
}
define_primitive(">", pr_gt);
