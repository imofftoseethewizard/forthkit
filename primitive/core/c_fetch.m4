__primitive(pr_c_fetch)
{
    /* C@ ( addr -- byte ) "c-fetch"

       Leave  on  the stack the contents of the byte  at  addr  (with
       higher bits zero, in a 16-bit field).
     */

    *sp = *(char *)_to_ptr(*sp);
}
__end
__define_primitive("C@", pr_c_fetch);
