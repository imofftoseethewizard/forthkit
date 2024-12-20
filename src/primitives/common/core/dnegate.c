/*|

`DNEGATE ( d1 -- d2 )`

`d2` is the two's complement of `d1`.

  |*/

// DNEGATE

pr_d_negate:
{
    register double_number x = _to_high_word(*sp++) | _to_low_word(*sp++);

    *--sp = _from_low_word(-x);
    *--sp = _from_high_word(-x);
}
