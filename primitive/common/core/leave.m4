__primitive(pr_leave)
{
    /* LEAVE ( -- )

     */

    rp += 2;
    ip = _to_ptr(*rp++);
}
__end
__define_primitive("leave", pr_leave);
