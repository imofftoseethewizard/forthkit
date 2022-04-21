__primitive(pr_sign)  
{

    if (*(number *)sp++ < 0)
        _hold('-');

}
__end
__define_primitive("SIGN", pr_sign);
