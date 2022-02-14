_primitive(pr_roll) {
    register cell tmp0 = *sp, tmp1 = *(sp + tmp0);
    register int i;

    for (i = tmp0; i > 0; i--)
        *(sp+i) = *(sp+i-1);

    *++sp = tmp1;
    _next();
}
_define_primitive("ROLL", pr_roll);
