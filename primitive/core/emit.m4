#define _emit() putc(*sp++, stdout)

primitive(pr_emit) {
    _emit();
    _next();
}
