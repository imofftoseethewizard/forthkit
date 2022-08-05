__primitive(pr_state)
{
    *--sp = _from_ptr(&tp[ta_state]);
    *sp = _from_ptr(&e[ea_state]);
}
__end
__define_primitive("state", pr_state);
