_primitive(pr_d_plus) {

    register double_number
      x = _to_high_word(*sp++) | _to_low_word(*sp++),
      y = _to_high_word(*sp++) | _to_low_word(*sp++),
      sum = x + y;

    *--sp = _from_low_word(sum);
    *--sp = _from_high_word(sum);

    _next();
}