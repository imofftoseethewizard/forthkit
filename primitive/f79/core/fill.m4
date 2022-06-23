__primitive(pr_fill)
{
    /* FILL ( addr n b -- )

       n bytes of memory beginning at addr are set to b. If the
       quantity n is less than or equal to zero, no action is
       taken.
     */

    if (*(number *)(sp+1) > 0)
        memset(_to_ptr(*(sp+2)), *sp, *(sp+1));

    sp += 3;
}
__end
__define_primitive("FILL", pr_fill);
