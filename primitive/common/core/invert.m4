__primitive(pr_invert)
{
    *sp = ~*sp;
}
__end
__define_primitive("invert", pr_invert);
