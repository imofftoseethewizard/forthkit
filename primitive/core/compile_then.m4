#define _compile_then() _compile_jump_target()

__primitive(pr_compile_then)  
{
    _compile_then();
}
__end
__define_immediate_primitive("THEN", pr_compile_then);
