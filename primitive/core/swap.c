
#define _swap() do { register cell tmp = *sp; *sp = *(sp+1), *(sp+1) = tmp; } while(0)

_primitive(pr_swap) {
    _swap();
    _next();
}
_define_primitive("SWAP", pr_swap);
