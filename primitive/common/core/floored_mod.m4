__primitive(pr_mod)
{
    /* MOD ( n1 n2 -- n3 )

       n3 is the remainder after dividing n1 by the divisor n2. n3
       has the same sign as n2 or is zero. An error condition
       results if the divisor is zero.

     */
    register number
      n2 = *sp++,
      n1 = *sp;

    if (!n2)
        _abort(err_division_by_zero);

    else if ((n1 ^ n2) & c_msb)
        *sp = (n1 % n2 + n2) % n2;

    else
        *sp = n1 % n2;
}
__end
__define_primitive("mod", pr_mod);
