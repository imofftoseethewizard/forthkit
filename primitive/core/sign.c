_primitive(pr_sign) {

    if (*(number *)sp++ < 0)
        _hold('-');

    _next();
}
_define_primitive("SIGN", pr_sign);
