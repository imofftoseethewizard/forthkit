define_primitive("@", pr_fetch);

#define _fetch() *sp = _fetch_addr(*sp)

if (0) {
  pr_fetch:
    _fetch();
    _next();
}
