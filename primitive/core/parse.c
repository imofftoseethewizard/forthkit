define_primitive("PARSE", pr_parse);

/* Aliases for some temporary variables to provide readability. */

if (0) {
  pr_parse:

    register char delimiter = *sp++;
    register int len = 0;

    *--sp = (cell)&source[point];

    while (point < source_len && source[point] != delimiter)
        len++, point++;

    *--sp = len;

    _next();
}
