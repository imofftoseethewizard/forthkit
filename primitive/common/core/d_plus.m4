__primitive(pr_d_plus)
{
    /* D+ ( d1 d2 --- d3 )  "d-plus"

       Leave the arithmetic sum of d1 plus d2.
     */

    register double_number
      x = _to_high_word(*sp++) | _to_low_word(*sp++),
      y = _to_high_word(*sp++) | _to_low_word(*sp++),
      sum = x + y;

    *--sp = _from_low_word(sum);
    *--sp = _from_high_word(sum);
}
__end
__define_primitive("d+", pr_d_plus);
