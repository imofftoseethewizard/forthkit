__primitive(pr_divide)
{
    /* / ( n1 n2 -- n3 ) "divide"

       n3 is the floor of the quotient of n1 divided by the divisor
       n2.  An error condition results if the divisor is zero.

     */
    register number
      n2 = *sp++,
      n1 = *sp;

    if (!n2)
        _abort(err_division_by_zero);

    else if ((n1 ^ n2) & c_msb)
        *sp = (n1 - (n2 - (n2 > 0 ? 1 : -1))) / n2;

    else
        *sp = n1 / n2;
}
__end
__define_primitive("/", pr_divide);
