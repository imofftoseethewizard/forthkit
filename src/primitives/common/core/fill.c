pr_fill:
{
    /* FILL ( addr u b -- )

       u bytes of memory beginning at addr are set to b.  No
       action is taken if u is zero.
     */

    if (*(sp+1))
        memset(_to_ptr(*(sp+2)), *sp, *(sp+1));

    sp += 3;
}
