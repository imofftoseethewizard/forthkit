__primitive(pr_d_negate)
{
    /* DNEGATE ( d1 -- d2 ) "d-negate"

       d2 is the two's complement of d1.
     */

    register double_number x = _to_high_word(*sp++) | _to_low_word(*sp++);

    *--sp = _from_low_word(-x);
    *--sp = _from_high_word(-x);
}
__end
__define_primitive("DNEGATE", pr_d_negate);
