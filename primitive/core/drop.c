
#define _drop() ++sp

_primitive(pr_drop) {
    _drop();
    _next();
}
define_primitive("DROP", pr_drop);
