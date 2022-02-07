
#define _fetch() *sp = *_to_ptr(*sp)

_primitive(pr_fetch) {
    _fetch();
    _next();
}
_define_primitive("@", pr_fetch);
