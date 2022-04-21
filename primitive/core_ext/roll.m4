__primitive(pr_roll)  
{
    register number n = *sp++ - 1;

    if (n >= 0) {

        register cell tmp = *(sp+n);
        register cell *src = sp + n - 1;
        register cell *dest = sp + n;

        for (; n > 0; n--)
            *dest-- = *src--;

        *sp = tmp;

    } else {
        *sp = -24;
        _abort();
    }
}
__end
__define_primitive("ROLL", pr_roll);
