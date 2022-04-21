__primitive(pr_leave)  
{
    *(rp+1) = *rp;
}
__end
__define_primitive("LEAVE", pr_leave);
