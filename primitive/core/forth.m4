__primitive(pr_forth)  
{
    tp[ta_context] = _from_ptr(&e[ea_forth]);
}
__end
__define_primitive("FORTH", pr_forth);
