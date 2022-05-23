#define _immediate(flags) _set_word_flags(_to_ptr(*_to_ptr(tp[ta_current])), c_immediate)

__primitive(pr_immediate)  
{
    _immediate();
}
__end
__define_primitive("IMMEDIATE", pr_immediate);
