__primitive(pr_c_move)  
{
    register number n = *sp++;
    register char *dest = (char *)_to_ptr(*sp++);
    register char *src = (char *)_to_ptr(*sp++);
    for (; n > 0; n--) *dest++ = *src++;
}
__end
__define_primitive("CMOVE", pr_c_move);