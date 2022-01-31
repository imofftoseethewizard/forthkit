
#define _fetch() *sp = *(cell *)(*sp)

_primitive(pr_fetch) {
    _fetch();
    _next();
}
define_primitive("@", pr_fetch);
