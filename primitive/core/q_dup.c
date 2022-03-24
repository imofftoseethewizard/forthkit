_primitive(pr_q_dup) {
    if (*sp) *--sp = *(sp+1);
    _next();
}
