_primitive(pr_div_mod) {
    register number
      q = (number)*sp++,
      n = (number)*sp++,
      r = n % q;

    if (n > 0 && r < 0)
        r += q > 0 ? q : -q;

    else if (n < 0 && r > 0)
        r += q < 0 ? q : -q;

    *--sp = r;
    *--sp = (n-r)/q;
    _next();
}
_define_primitive("/MOD", pr_div_mod);
