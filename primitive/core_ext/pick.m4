__primitive(pr_pick)
{
    register number n = *sp;
    if (n >= 1)
        *sp = *(sp + n);
    else
        _abort(-24); /* invalid numeric argument */
}
__end
__define_primitive("PICK", pr_pick);
