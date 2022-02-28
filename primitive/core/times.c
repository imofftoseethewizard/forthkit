#define _times() *++sp = (number)*(sp+1) * (number)*sp

_primitive(pr_times) {
    _times();
    _next();
}
_define_primitive("*", pr_times);
