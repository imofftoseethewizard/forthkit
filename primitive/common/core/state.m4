#define _state() *--sp = _from_ptr(&tp[ta_state])

__primitive(pr_state)  
{
    _state();
}
__end
__define_primitive("STATE", pr_state);
