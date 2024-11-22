pr_times_divide_mod:
{
    /*  * /mod ( n1 n2 n3 -- n4 n5 ) "times-divide-mod"

        ( Note: due to conflict with C's comment end token, there
        is a space in the word's name above.)

        n1 is first multiplied by n2 producing an intermediate
        double cell result. n4 is the floor of the quotient of the
        intermediate result divided by the divisor n3. The
        product of n1 times n2 is maintained as an intermediate
        double cell result for greater precision than the otherwise
        equivalent sequence: "n1 n2 * n3 /mod". n4 has the same sign
        as n3 or is zero. An error condition results if the divisor
        is zero or if the quotient falls outside of the range of a
        signed single cell.
     */

    register number
      n3 = (number)*sp++,
      n2 = (number)*sp++,
      n1 = (number)*sp++;

    if (!n3)
        _abort(err_division_by_zero);

    else {
        register double_number
          p = _to_low_word(n1) * _to_low_word(n2),
          q = p / _to_low_word(n3),
          r = p % _to_low_word(n3);

        register number q_l, q_h;

        if (r && (_from_high_word(r) ^ n3) & c_msb) {
            r += n3;
            q -= 1;
        }

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
