#define _store() *_to_ptr(*sp) = *(sp+1), sp += 2

_primitive(pr_store) {
    _store();
    _next();
}
_define_primitive("!", pr_store);
