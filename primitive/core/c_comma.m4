__primitive(pr_c_comma)  
{
    *here++ = (char)*sp++;
}
__end
__define_primitive(`"C,"', pr_c_comma);
