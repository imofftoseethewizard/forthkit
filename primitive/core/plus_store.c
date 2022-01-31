
#define _plus_store() *(*sp++) += *(sp+1)

_primitive(pr_plus_store) {
    _plus_store();
    _next();
}
define_primitive("+!", pr_plus_store);
