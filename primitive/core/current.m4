__primitive(pr_current)  
{
    *--sp = _from_ptr(&e[ea_current]);
}
__end
__define_primitive("CURRENT", pr_current);
