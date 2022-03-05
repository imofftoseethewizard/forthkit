_primitive(pr_u_dot) {
    register cell u = *sp;
    register cell base = e[ea_base];

    _num_start();

    _hold(' ');

    do {
        _hold(_digit(u % base));
        u /= base;
    } while (u);

    /* _num_end expects a double number on the stack */
    sp--;
    _num_end();
    _type();

    _next();
}

_define_primitive("u.", pr_u_dot);
