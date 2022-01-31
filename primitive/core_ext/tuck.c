
#define _tuck() *--sp = *(sp+2)

_primitive(pr_tuck) {
    _tuck();
    _next();
}
define_primitive("TUCK", pr_tuck);
