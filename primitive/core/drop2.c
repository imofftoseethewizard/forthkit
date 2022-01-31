
#define _drop2() sp += 2

_primitive(pr_drop2) {
    _drop2();
    _next();
}
define_primitive("2DROP", pr_drop2);
