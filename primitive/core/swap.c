
#define _swap() tmp0 = *sp, *sp = *(sp+1), *(sp+1) = tmp0

_primitive(pr_swap) {
    _swap();
    _next();
}
_define_primitive("SWAP", pr_swap);
