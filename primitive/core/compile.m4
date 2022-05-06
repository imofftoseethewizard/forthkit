__primitive(pr_compile)  
{
    *(cell *)dp = *ip++;
}
__end
__define_primitive("COMPILE", pr_compile);
