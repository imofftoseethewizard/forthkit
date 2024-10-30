primitive pr_divide()
{
    /* / ( n1 n2 -- n3 ) "divide"

       Divide  n1  by n2 and leave the quotient n3.   n3  is  rounded
       toward zero. An error condition results if the divisor is zero.

     */

    if (*sp)
        *++sp = (number)*(sp+1) / (number)*sp;
    else
        _abort(err_division_by_zero);
}
