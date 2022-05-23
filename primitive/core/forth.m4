__primitive(pr_forth)  
{
    tp[ta_context] = _from_ptr(&tp[ta_forth]);
}
__end
__define_primitive("FORTH", pr_forth);
