__primitive(pr_c_comma)
{
    *dp++ = (char)*sp++;
    _check_dictionary_bounds();
}
__end
__define_primitive(`"C,"', pr_c_comma);
