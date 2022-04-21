__primitive(pr_rot)  
{
    register cell tmp = *sp;
    *sp = *(sp+2), *(sp+2) = *(sp+1), *(sp+1) = tmp;
}
__end
__define_primitive("ROT", pr_rot);
