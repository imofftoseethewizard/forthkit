define_primitive("PARSE-NAME", pr_parse_name);

if (0) {
  pr_parse_name:

    /* ASCII space */
    register char delimiter = 32;

    while (point < source_len && source[point] == delimiter)
        point++;

    *--sp = delimiter;

    goto pr_parse;
}

#undef delimiter
