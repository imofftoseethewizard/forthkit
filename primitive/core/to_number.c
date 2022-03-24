_primitive(pr_to_number) {

    register number base, digit, len, result;
    register char *s;

    base = e[ea_base];
    len = *sp;
    s = (char *)_to_ptr(*(sp+1));
    result = *(sp+2);

    if (*s == '-')
        s++, len--;

    while (0 < len) {
        digit = _parse_digit(*s);

        if (digit < 0 || digit > base)
            break;

        result = result * base + digit;
        s++, len--;
    }

    if (*(char *)_to_ptr(*(sp+1)) == '-')
        result *= -1;

    *(sp+2) = result;
    *(sp+1) = _from_ptr(s);
    *sp = len;

    _next();
}
