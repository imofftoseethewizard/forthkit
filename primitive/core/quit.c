_primitive(pr_quit) {
    rp = rp0;
    ip = 0;
    _next();
}

_define_primitive("QUIT", pr_quit);
