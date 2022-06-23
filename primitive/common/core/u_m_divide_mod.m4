__primitive(pr_u_m_divide_mod)
{
    /* UM/MOD ( ud u1 -- u2 u3 ) "u-m-divide-mod"

       u2 is the remainder and u3 is the floor of the quotient
       after dividing ud by the divisor u1.  All values and
       arithmetic are unsigned.  An error condition results if the
       divisor is zero or if the quotient lies outside the range
       of a single cell.
     */

    register cell u1 = *sp++;
    register double_cell ud = _to_high_word(*sp++) | _to_low_word(*sp++);

    if (!u1)
        _abort(err_division_by_zero);

    else {
        register double_cell
          q = ud / u1,
          r = ud % u1;

        register cell q_l, q_h;

        q_l = _from_low_word(q);
        q_h = _from_high_word(q);

        if (q_l > 0 && q_h || q_l < 0 && q_h != -1)
            _abort(err_result_out_of_range);

        else {
            *--sp = _from_low_word(r);
            *--sp = q_l;
        }
    }
}
__end
__define_primitive("UM/MOD", pr_u_m_divide_mod)
