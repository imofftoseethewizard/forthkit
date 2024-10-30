primitive pr_leave()
{
    /* LEAVE ( -- )

     */

    rp += 2;
    ip = _to_ptr(*rp++);
}
