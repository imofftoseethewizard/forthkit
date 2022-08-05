__primitive(pr_2_r_from)
{
    sp -= 2;
    *(sp+1) = *(rp+1);
    *sp = *rp;
    rp += 2;
}
__end
__define_primitive("2r>", pr_2_r_from);
