__primitive(pr_divide_mod)
{
    /* /MOD ( n1 n2 -- n3 n4 ) "divide-mod"
       Divide  n1 by n2 and leave the remainder n3 and quotient n4.
       n3 has the same sign as n1.

     */

    register number
      n2 = (number)*sp++,
      n1 = (number)*sp++;

    if (!n2)
        _abort(err_division_by_zero);

    else {
        register number
          q = n1 / n2,
          r = n1 % n2;

        if (r && (r ^ n1) & c_msb) {

            if ((r ^ n2) & c_msb) {
                r += n2;
                q -= 1;

            } else {
                r -= n2;
                q += 1;
            }
        }

        *--sp = r;
        *--sp = q;
    }
}
__end
__define_primitive("/mod", pr_divide_mod);
