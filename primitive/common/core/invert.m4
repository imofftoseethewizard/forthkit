__primitive(pr_invert)
{
    *sp = ~*sp;
}
__end
__define_primitive("INVERT", pr_invert);
