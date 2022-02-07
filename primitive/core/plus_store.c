#define _plus_store() *_to_ptr(*sp) += *(sp+1), sp += 2

_primitive(pr_plus_store) {
    _plus_store();
    _next();
}
_define_primitive("+!", pr_plus_store);
