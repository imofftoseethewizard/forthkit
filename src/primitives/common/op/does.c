/*|

Note ip points to the cell after op_does. That cell contains the
address of the code following does>.  After that is the first cell of
the parameter field for the word defined by the word containing does>.

  |*/

op_does:
{
    *--sp = _from_ptr(ip + 2); /* skip over does> code addr, op_exit */
    ip = _to_ptr(*ip);
}
