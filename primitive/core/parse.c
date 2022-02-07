
/* Aliases for some temporary variables to provide readability. */

_primitive(pr_parse) {

    register char delimiter = *sp++;
    register int len = 0;

    *--sp = (cell)&source[point];

    while (point < source_len && source[point] != delimiter)
        len++, point++;

    *--sp = len;

    _next();
}
_define_primitive("PARSE", pr_parse);
