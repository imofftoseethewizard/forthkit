void _bury(number n)
{
    register i;

    if (!_is_valid_stack_index(n))
        _abort(err_invalid_numeric_argument);

    for (i = 0; i <= n; i++)
        *(sp + i - 1) = *(sp + i);

    *(sp + n) = *(sp-1);
}

void _pick(number n)
{
    register number n = *sp++;

    if (!_is_valid_stack_index(n))
        _abort(err_invalid_numeric_argument);

    else
        *--sp = *(sp + n);
}

void _poke(number n)
{
    register i;

    if (!_is_valid_stack_index(n))
        _abort(err_invalid_numeric_argument);

    for (i = 0; i <= n; i++)
        *(sp + i - 1) = *(sp + i);

    *(sp + n) = *(sp-1);

    sp--;
}

void _roll(number n)
{
    if (!n)
        ;

    else if (!_is_valid_stack_index(n))
        _abort(err_invalid_numeric_argument);

    else {
        register cell tmp = *(sp+n);
        register cell *src = sp + n - 1;
        register cell *dest = sp + n;

        for (; n > 0; n--)
            *dest-- = *src--;

        *sp = tmp;
    }
}

primitive bury()
{
    _bury(*sp++);
}

primitive bury_op()
{
    _bury(*ip++);
}

primitive drop()
{
    sp++;
}

primitive dup()
{
    sp--;
    *sp = *(sp+1);
}

primitive nip()
{
    sp++;
    *sp = *(sp-1);
}

primitive over()
{
    sp--;
    *sp = *(sp+2);
}

primitive pick()
{
    _pick(*sp++);
}

primitive pick_op()
{
    _pick(*ip++);
}

primitive poke()
{
    _poke(*sp++);
}

primitive poke_op()
{
    _poke(*ip++);
}

primitive roll()
{
    _roll(*sp++);
}

primitive roll_op()
{
    _roll(*ip++);
}

primitive rot()
{
    register cell tmp = *sp;
    *sp = *(sp+2);
    *(sp+2) = *(sp+1);
    *(sp+1) = tmp;
}

primitive swap()
{
    register cell tmp = *sp;
    *sp = *(sp+1);
    *(sp+1) = tmp;
}

primitive tuck()
{
    sp--;
    *sp = *(sp+1);
    *(sp+1) = *(sp+2);
    *(sp+2) = *sp;
}
