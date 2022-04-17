primitive(pr_u_times) {

    register double_cell
      x = _to_low_word(*sp++),
      y = _to_low_word(*sp++),
      p = x * y;

    *--sp = _from_low_word(p);
    *--sp = _from_high_word(p);

    _next();
}
