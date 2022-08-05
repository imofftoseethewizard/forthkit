__primitive(pr_divide_mod)
{
    /* /MOD ( n1 n2 -- n3 n4 ) "divide-mod"

       n3 is the remainder and n4 the floor of the quotient of n1
       divided by the divisor n2.  n3 has the same sign as n2 or is
       zero.  An error condition results if the divisor is zero.
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

        if (r && (r ^ n2) & c_msb) {
            r += n2;
            q -= 1;
        }

        *--sp = r;
        *--sp = q;
    }
}
__end
__define_primitive("/mod", pr_divide_mod);
