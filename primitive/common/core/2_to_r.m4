__primitive(pr_2_to_r)
{
    rp -= 2;
    *(rp+1) = *(sp+1);
    *rp = *sp;
    sp += 2;
}
__end
__define_primitive("2>r", pr_2_to_r);
