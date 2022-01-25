define_primitive("WORD", &&pr_word);

/* Aliases for some temporary variables to provide readability. */
#define delimiter  k
#define word_point i

if (0) {
  pr_word:
     /* Delimiter is on the top of the stack. */
     delimiter = *sp++;

     word_point = sizeof(length_type);

     /* Skip leading delimiters. */
     while (point < source_len && source[point] == delimiter)
          point++;

     /* Copy word from source to word buffer. */
     while (point < source_len && word_point < word_buffer_len
            && source[point] != delimiter)
          word_buffer[word_point++] = source[point++];

     *(length_type *)word_buffer = (length_type)(word_point - sizeof(length_type));

     *--sp = (cell)word_buffer;

     _next();
}

#undef delimiter
#undef word_point
