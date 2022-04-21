__primitive(pr_forth)  
{
    e[ea_context] = _from_ptr(&e[ea_forth]);
}
__end
__define_primitive("FORTH", pr_forth);
