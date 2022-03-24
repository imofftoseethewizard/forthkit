_primitive(pr_num) {
    register double_cell n = _to_high_word(*sp++) | _to_low_word(*sp++);

    _hold(_digit(n % e[ea_base]));
    n /= e[ea_base];

    *--sp = _from_low_word(n);
    *--sp = _from_high_word(n);

    _next();
}
