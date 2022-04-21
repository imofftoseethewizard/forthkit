#define _u_lt() *++sp = *(sp+1) < *sp

__primitive(pr_u_lt)  
{
    _u_lt();
}
__end
__define_primitive("U<", pr_u_lt);
