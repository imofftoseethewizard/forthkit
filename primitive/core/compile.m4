__primitive(pr_compile)  
{
    *(cell *)here = *ip++;
}
__end
__define_primitive("COMPILE", pr_compile);
