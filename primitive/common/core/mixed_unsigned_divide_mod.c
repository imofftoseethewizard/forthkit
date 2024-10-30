primitive pr_mixed_unsigned_divide_mod()
{
    /* ud/mod ( ud1 u2 -- urem udquot )

       Divide unsigned double ud1 by u2, resulting in an unsigned
       double quotient udquot and a single remainder urem.
    */

    register cell
      u2 = *sp++,
      ud1_high = *sp++,
      ud1_low = *sp++;

    register double_cell ud1 = _to_low_word(ud1_low) | _to_high_word(ud1_high);

    if (!u2)
        _abort(err_division_by_zero);

    else {
        register double_cell udquot = ud1 / u2;

        *--sp = ud1 % u2;
        *--sp = _from_low_word(udquot);
        *--sp = _from_high_word(udquot);
    }
}
