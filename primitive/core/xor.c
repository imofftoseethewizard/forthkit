
#define _xor() *++sp = *(sp+1) ^ *sp

_primitive(pr_xor) {
    _xor();
    _next();
}
define_primitive("XOR", pr_xor);
