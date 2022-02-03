
#define _fetch() *sp = _fetch_addr(*sp)

_primitive(pr_fetch) {
    _fetch();
    _next();
}
define_primitive("@", pr_fetch);
