#define _key() *--sp = getc(stdin)

_primitive(pr_key) {
    _key();
    _next();
}
_define_primitive("KEY", pr_key);
