__primitive(pr_context)  
{
    *--sp = _from_ptr(&tp[ta_context]);
}
__end
__define_primitive("CONTEXT", pr_context);
