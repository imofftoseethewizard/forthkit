
#define _drop() ++sp

_primitive(pr_drop) {
    _drop();
    _next();
}
_define_primitive("DROP", pr_drop);
