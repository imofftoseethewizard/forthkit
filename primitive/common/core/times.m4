/* * ( n1 n2 -- n3 ) "times"

   Leave the arithmetic product of n1 times n2.
 */
#define _times() *++sp = (number)*(sp+1) * (number)*sp

__primitive(pr_times)
{
    /* * ( n1 n2 -- n3 ) "times"

       Leave the arithmetic product of n1 times n2.
     */
    _times();
}
__end
__define_primitive("*", pr_times);
