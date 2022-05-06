__primitive(pr_c_comma)  
{
    *dp++ = (char)*sp++;
}
__end
__define_primitive(`"C,"', pr_c_comma);
