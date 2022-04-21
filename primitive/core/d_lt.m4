__primitive(pr_d_lt)  
{
    register double_number
      x = _to_high_word(*sp++) | _to_low_word(*sp++),
      y = _to_high_word(*sp++) | _to_low_word(*sp++);

    *--sp = (cell)(y < x);
}
__end
__define_primitive("D<", pr_d_lt);
