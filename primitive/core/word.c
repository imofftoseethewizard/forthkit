define_primitive("word", &&p1_word);

/* Aliases for some temporary variables to provide readability. */
#define source_end cp0
#define word_point cp1
#define word_buffer_end cp2

if (0) {
  p1_word:
     /* Delimiter is on the top of the stack. */
     k = *sp++;

     source_end = source + source_len;
     word_point = word_buffer + sizeof(length_type);
     word_buffer_end = word_buffer + word_buffer_len;

     /* Skip leading delimiters. */
     while (point < source_end && *point == k)
          point++;

     /* Copy word from source to word buffer. */
     while (point < source_end && word_point < word_buffer_end && *point != k)
          *word_point++ = point++;

     *(length_type *)word_buffer =
       (length_type)(word_point - word_buffer - sizeof(length_type));

     *--sp = (cell)word_buffer;

     next();
}

#undef source_end
#undef word_point
#undef word_buffer_end
