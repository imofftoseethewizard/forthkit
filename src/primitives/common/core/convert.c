/*|

`CONVERT ( ud1 addr1 -- ud2 addr2 )`

`ud2` is the result of converting the characters within the text
beginning at `addr1+2` into digits, using the value of `BASE`, and
accumulating each into `ud1` after multiplying `ud1` by the value of
`BASE`.  Conversion continues until an unconvertible character is
encounter.  `addr2` is the location of the first unconvertible
character.

  |*/

// CONVERT

pr_convert:
{
    register number base, digit;
    register double_number result;
    register char *s;

    base = tp[ta_base];
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

}
