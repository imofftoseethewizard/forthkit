__primitive(pr_to_r)  
{
    *--rp = *sp++;
}
__end
__define_primitive(">R", pr_to_r);
