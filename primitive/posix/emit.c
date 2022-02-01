define_primitive("EMIT", pr_emit);

#define _emit() putc(*sp++, stdout)

if (0) {
  pr_emit:
    print_stack(sp0, sp);
    _emit();
    _next();
}
