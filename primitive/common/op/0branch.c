/*|

op_0branch pops the top of the stack.  If it is non-zero, it advances
ip one cell and continues.  If it is zero, it reads the value at ip
and adds that to ip before continuing.  In effect, the consequent of
the branch begins immediately after the offset, while the offset
provides the jump distance to the alternate.

  |*/

op_0branch:
{

    if (*sp++)
        /* skip over offset to alternate */
        ip++;
    else
        ip = (cell *)((char *)ip + (number)*ip);
}
