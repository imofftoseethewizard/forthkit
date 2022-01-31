
#define _allot() here += *sp++

_primitive(pr_allot) {
    _allot();
    _next();
}
define_primitive("ALLOT", pr_allot);
