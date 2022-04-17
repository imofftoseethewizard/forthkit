primitive(pr_times_div_mod) {
    register double_number
      q = _to_low_word((number)*sp++),
      m = _to_low_word((number)*sp++),
      n = _to_low_word((number)*sp++),
      p = m * n,
      r = p % q;

    if (n > 0 && r < 0)
        r += q > 0 ? q : -q;

    else if (n < 0 && r > 0)
        r += q < 0 ? q : -q;

    *--sp = _from_low_word(r);
    *--sp = _from_low_word((p-r)/q);
    _next();
}
