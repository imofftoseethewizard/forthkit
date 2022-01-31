
#define _emit() putc(*sp++, stdout)

_primitive(pr_emit) {
    _emit();
    _next();
}
define_primitive("EMIT", pr_emit);
