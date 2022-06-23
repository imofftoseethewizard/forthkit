__primitive(pr_fetch)
{
    /* @ ( addr -- n ) "fetch"

     Leave on the stack the number contained at addr.
     */
    *sp = *_to_ptr(*sp);
}
__end
__define_primitive("@", pr_fetch);
