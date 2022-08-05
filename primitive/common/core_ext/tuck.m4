__primitive(pr_tuck)
{
    *(sp-1) = *sp;
    *sp = *(sp+1);
    *(sp+1) = *(sp-1);
    sp--;
}
__end
__define_primitive("tuck", pr_tuck);
