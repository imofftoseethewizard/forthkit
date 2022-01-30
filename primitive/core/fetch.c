define_primitive("@", pr_fetch);

#define _fetch() *sp = *(cell *)(*sp)

if (0) {
  pr_fetch:
    _fetch();
    _next();
}
