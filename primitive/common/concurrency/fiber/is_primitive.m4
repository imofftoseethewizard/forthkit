__primitive(pr_is_primitive)
{
    *sp = !!_is_primitive(*sp);
}
__end
__define_primitive("primitive?", pr_is_primitive);
