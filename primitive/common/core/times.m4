__primitive(pr_times)
{
    /* * ( n1 n2 -- n3 ) "times"

       Leave the arithmetic product of n1 times n2.
     */
    *++sp = (number)*(sp+1) * (number)*sp;
}
__end
__define_primitive("*", pr_times);
