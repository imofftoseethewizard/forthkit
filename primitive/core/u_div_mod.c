_primitive(pr_u_div_mod) {
    register cell u = *sp++;
    register double_cell ud = _to_high_word(*sp++) | _to_low_word(*sp++);

    *--sp = ud % u;
    *--sp = ud / u;

    _next();
}
