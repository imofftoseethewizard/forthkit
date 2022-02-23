#define _gt() *++sp = (number)*(sp+1) >  (number)*sp

_primitive(pr_gt) {
    _gt();
    _next();
}
_define_primitive(">", pr_gt);
