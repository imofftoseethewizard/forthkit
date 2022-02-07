#define _times() *++sp = *(sp+1) * *sp

_primitive(pr_times) {
    _times();
    _next();
}
_define_primitive("*", pr_times);
