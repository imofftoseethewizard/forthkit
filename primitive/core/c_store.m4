__primitive(pr_c_store)  
{
    *(char *)_to_ptr(*sp) = (char)*(sp+1);
    sp += 2;
}
__end
__define_primitive("C!", pr_c_store);
