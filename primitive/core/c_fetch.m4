__primitive(pr_c_fetch)  
{
    *sp = *(char *)_to_ptr(*sp);
}
__end
__define_primitive("C@", pr_c_fetch);
