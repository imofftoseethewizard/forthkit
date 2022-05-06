 /* Note that this assumes that a cell is an power of 2 number of bytes.
    That seems like a safe assumption.
 */

#define _align(x) (cell *)((long)(x) + sizeof(cell) - 1 & ~(sizeof(cell) - 1))

__primitive(pr_align)  
{
    dp = (char *)_align(dp);
}
__end
__define_primitive("ALIGN", pr_align);
