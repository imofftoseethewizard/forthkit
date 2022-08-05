__primitive(pr_2_r_fetch)
{
    sp -= 2;
    *(sp+1) = *(rp+1);
    *sp = *rp;
}
__end
__define_primitive("2r@", pr_2_r_fetch);
