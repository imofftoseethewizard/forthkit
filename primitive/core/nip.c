
#define _nip() *++sp = *(sp-1)

_primitive(pr_nip) {
    _nip();
    _next();
}
_define_primitive("NIP", pr_nip);
