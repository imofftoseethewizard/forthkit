__primitive(pr_fill)  
{

    if (*(number *)(sp+1) > 0)
        memset(_to_ptr(*(sp+2)), *sp, *(sp+1));

    sp += 3;
}
__end
__define_primitive("FILL", pr_fill);
