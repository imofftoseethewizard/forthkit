primitive pr_gt()
{
    /* > ( n1 n2 -- flag ) "greater-than"

       flag is true if n1 is greater than n2.
     */
    *++sp = (number)*(sp+1) >  (number)*sp;
}
