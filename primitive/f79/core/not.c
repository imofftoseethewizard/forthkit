primitive pr_not()
{
    /* NOT ( flag1 -- flag2 )

       Reverse the boolean value of flag1.  This is identical to 0=.
     */

    *sp = *sp == 0;
}
