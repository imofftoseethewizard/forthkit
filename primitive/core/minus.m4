/* - ( n1 n2 -- n3 ) "minus"

   Subtract n2 from n1 and leave the difference n3.
 */

#define _minus() *++sp = *(sp+1) - *sp

__primitive(pr_minus)
{
    /* - ( n1 n2 -- n3 ) "minus"

       Subtract n2 from n1 and leave the difference n3.
     */
    _minus();
}
__end
__define_primitive("-", pr_minus);
