__primitive(pr_lt)
{
    /* < ( n1 n2 -- flag ) "less-than"

       flag is true if n1 is less than n2.
     */
    *++sp = (number)*(sp+1) < (number)*sp;
}
__end
__define_primitive("<", pr_lt);
