/*|

`C@ ( addr -- byte )`

Leave on the stack the contents of the byte at addr (with higher bits
zero, in a 16-bit field).

  |*/

// C@

pr_c_fetch:
{
    *sp = *(char *)_to_ptr(*sp);
}
