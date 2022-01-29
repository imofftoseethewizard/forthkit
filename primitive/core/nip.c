define_primitive("NIP", &&pr_nip);

#define _nip() *++sp = *(sp-1)

if (0) {
  pr_nip:
    _nip();
    _next();
}
