_primitive(pr_convert) {

    register number base, digit;
    register double_number result;
    register char *s;

    base = e[ea_base];
    s = (char *)_to_ptr(*sp);
    result = _to_high_word(*(sp+1)) | _to_low_word(*(sp+2));

    if (*s == '-')
        s++;

    while (1) {
        digit = _parse_digit(*s);

        if (digit < 0 || digit > base)
            break;

        result = result * base + digit;
        s++;
    }

    if (*(char *)_to_ptr(*sp) == '-')
        result *= -1;

    *(sp+2) = _from_low_word(result);
    *(sp+1) = _from_high_word(result);
    *sp = _from_ptr(s);

    _next();
}