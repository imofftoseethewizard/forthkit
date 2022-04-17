primitive(pr_sign) {

    if (*(number *)sp++ < 0)
        _hold('-');

    _next();
}
