__primitive(pr_r_fetch)  
{
    *--sp = *rp;
}
__end
__define_primitive("R@", pr_r_fetch);
