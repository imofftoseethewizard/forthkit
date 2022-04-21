#define _to_in() *--sp = _from_ptr(&e[ea_source_idx])

__primitive(pr_to_in)  
{
    _to_in();
}
__end
__define_primitive(">IN", pr_to_in);
