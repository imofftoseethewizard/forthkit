__primitive(pr_unloop)
{
    /* drop loop index, limit, and leave addr from return stack. */
    rp += 3;
}
__end
__define_primitive("UNLOOP", pr_unloop);
