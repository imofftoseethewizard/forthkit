/*|

`CMOVE ( addr1 addr2 u -- )`

Move u bytes beginning at address addr1 to addr2.  The byte at addr1
is moved first, proceeding toward high memory.  If u is zero nothing
is moved.

  |*/

// CMOVE

pr_c_move:
{
    register cell u = *sp++;
    register char *dest = (char *)_to_ptr(*sp++);
    register char *src = (char *)_to_ptr(*sp++);
    for (; u != 0; u--) *dest++ = *src++;
}
