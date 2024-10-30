primitive pr_divide()
{
    /* / ( n1 n2 -- n3 ) "divide"

       n3 is the floor of the quotient of n1 divided by the divisor
       n2.  An error condition results if the divisor is zero.

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

        if (r && (r ^ n2) & c_msb)
            q -= 1;

        *--sp = q;
    }
}
