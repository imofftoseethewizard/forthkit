define_primitive("ALIGN", &&pr_align);

if (0) {
  pr_align:
    here = (char *)_align(here);
    _next();
}
