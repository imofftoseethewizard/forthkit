pr_c_store:
{
    /* C! ( n addr -- ) "c-store"

     Store the least significant 8-bits of n at addr.
     */

    *(char *)_to_ptr(*sp) = (char)*(sp+1);
    sp += 2;
}
