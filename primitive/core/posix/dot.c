_primitive(pr_dot) {
    register number n = (number)*sp;
    register cell base = e[ea_base];

    n = n < 0 ? -n : n;

    _num_start();

    _hold(' ');

    do {
        _hold(_digit(n % base));
        n /= base;
    } while (n);

    if ((number)*sp < 0)
        _hold('-');

    sp++;

    _num_end();
    _type();

    _next();
}

_define_primitive(".", pr_dot);
