/*|

`D< ( d1 d2 -- flag )`

`flag` is true if `d1` is less than `d2` according to the operation of
`<` except extended to a double word.

  |*/

// D<

pr_d_lt:
{
    register double_number
      x = _to_high_word(*sp++) | _to_low_word(*sp++),
      y = _to_high_word(*sp++) | _to_low_word(*sp++);

    *--sp = (cell)(y < x);
}
