define_primitive(">NUMBER", pr_to_number);

#define _parse_digit(c) \
        '0' <= c && c <= '9' ? (c - '0') \
      : 'A' <= c && c <= 'Z' ? (c - 'A' + 10) \
      : 'a' <= c && c <= 'z' ? (c - 'a' + 10) \
      : -1


if (0) {
  pr_to_number:
    print_stack(sp0, sp);

    register cell base, digit, len, result;
    register char *s;

    base = e[ea_base];
    len = *sp;
    s = (char *)_to_native_ptr(*(sp+1));
    result = *(sp+2);

    while (0 < len) {
        digit = _parse_digit(*s);

        if (digit < 0 || digit > base)
            break;

        result = result * base + digit;
        s++, len--;
    }

    *(sp+2) = result;
    *(sp+1) = _from_native_ptr(s);
    *sp = len;

    _next();
}
