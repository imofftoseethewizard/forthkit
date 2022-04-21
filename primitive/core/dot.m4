__primitive(pr_dot)  
{
    register number n = (number)*sp;
    register cell base = e[ea_base];

    n = n < 0 ? -n : n;

    _num_start();

    _hold(' ');

    do {
        _hold(_digit(n % base));
        n /= base;
    } while (n);

    if ((number)*sp < 0)
        _hold('-');

    /* _num_end expects a double number on the stack */
    sp--;
    _num_end();
    _type();

}
__end
__define_primitive(".", pr_dot);
