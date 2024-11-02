pr_store:
{
    /* ! ( n addr -- )

       Store n at addr.

       module: core
     */

    *_to_ptr(*sp) = *(sp+1);
    sp += 2;
}
