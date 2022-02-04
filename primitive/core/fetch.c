
#define _fetch() *sp = *_to_native_ptr(*sp)

_primitive(pr_fetch) {
    _fetch();
    _next();
}
define_primitive("@", pr_fetch);
