define_primitive("PARSE-NAME", &&pr_parse_name);

/* ASCII space */
#define delimiter 32

if (0) {
  pr_parse_name:

     while (point < source_len && source[point] == delimiter)
          point++;

    goto pr_parse;
}

#undef delimiter
