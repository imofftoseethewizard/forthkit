pr_zero_lt:
{
    /* 0< ( n -- flag ) "zero-less"

       flag is true if n is less than zero (negative).
     */
    *sp = (number)*sp < 0;
}
