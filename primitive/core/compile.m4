__primitive(pr_compile)
{
    *(cell *)dp = *ip++;
    _check_dictionary_bounds();
}
__end
__define_primitive("COMPILE", pr_compile);
