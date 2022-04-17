#define _xor() *++sp = *(sp+1) ^ *sp

primitive(pr_xor) {
    _xor();
    _next();
}
