define_primitive("PARSE", &&pr_parse);

/* Aliases for some temporary variables to provide readability. */
#define delimiter   k
#define len         j

if (0) {
  pr_parse:

    delimiter = *sp++;

    *--sp = (cell)&source[point];

    len = 0;

    while (point < source_len && source[point] != delimiter)
        len++, point++;

    *--sp = len;

    _next();
}

#undef delimiter
#undef len
