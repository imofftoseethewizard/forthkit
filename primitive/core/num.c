#define _digit(x) ((x) <= 9 ? '0' + (x) : 'a' + (x) - 10)

_primitive(pr_num) {
    register double_cell n = _to_high_word(*sp++) | _to_low_word(*sp++);

    _hold(_digit(n % e[ea_base]));
    n /= e[ea_base];

    *--sp = _from_low_word(n);
    *--sp = _from_high_word(n);

    _next();
}
_define_primitive("#", pr_num);
