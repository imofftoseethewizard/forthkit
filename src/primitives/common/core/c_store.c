/*|

`C! ( n addr -- )`

Store the least significant 8-bits of n at addr.

  |*/

// C!

pr_c_store:
{
    *(char *)_to_ptr(*sp) = (char)*(sp+1);
    sp += 2;
}
