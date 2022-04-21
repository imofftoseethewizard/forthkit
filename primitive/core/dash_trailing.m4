__primitive(pr_dash_trailing)  
{
    register number n = (number)*sp;
    register char *s = (char *)_to_ptr(*(sp+1));

    while (n > 0 && s[n-1] == 32)
        n--;

    *sp = n;
}
__end
__define_primitive("-TRAILING", pr_dash_trailing);
