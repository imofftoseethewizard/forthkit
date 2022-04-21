#define _swap() do { register cell tmp = *sp; *sp = *(sp+1), *(sp+1) = tmp; } while(0)

__primitive(pr_swap)  
{
    _swap();
}
__end
__define_primitive("SWAP", pr_swap);
