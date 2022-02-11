_primitive(pr_pick) {
    *sp = *(sp + *sp + 1);
    _next();
}

_define_primitive("PICK", pr_pick);
