
#define _pick() *sp-- = *(sp + 1 + *(sp+1))

_primitive(pr_pick) {
    _pick();
    _next();
}
_define_primitive("PICK", pr_pick);
