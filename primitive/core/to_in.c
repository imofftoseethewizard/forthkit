
#define _to_in() *sp-- = (cell)point;

_primitive(pr_to_in) {
    _to_in();
    _next();
}
define_primitive(">IN", pr_to_in);
