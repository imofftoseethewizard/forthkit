#define _allot() here += (number)*sp++

_primitive(pr_allot) {
    _allot();
    _next();
}
_define_primitive("ALLOT", pr_allot);
