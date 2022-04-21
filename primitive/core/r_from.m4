__primitive(pr_r_from)  
{
    *--sp = *rp++;
}
__end
__define_primitive("R>", pr_r_from);
