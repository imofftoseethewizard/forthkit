#define _swap() do { register cell tmp = *sp; *sp = *(sp+1), *(sp+1) = tmp; } while(0)

primitive(pr_swap) {
    _swap();
    _next();
}
