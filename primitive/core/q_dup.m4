__primitive(pr_q_dup)  
{
    if (*sp) *--sp = *(sp+1);
}
__end
__define_primitive("?DUP", pr_q_dup);
