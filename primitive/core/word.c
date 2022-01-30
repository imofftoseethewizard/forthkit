define_primitive("WORD", pr_word);

if (0) {
  pr_word:

    /* Delimiter is on the top of the stack. */
    register char delimiter = *sp++;
    register char *word_buffer = top - MAX_WORD_LENGTH;
    register int word_idx = sizeof(length_type);

    /* Skip leading delimiters. */
    while (source_idx < source_len && source[source_idx] == delimiter)
        source_idx++;

    /* Copy word from source to word buffer. */
    while (source_idx < source_len && word_idx < MAX_WORD_LENGTH
           && source[source_idx] != delimiter)
        word_buffer[word_idx++] = source[source_idx++];

    *(length_type *)word_buffer = (length_type)(word_idx - sizeof(length_type));

    *--sp = (cell)word_buffer;

    _next();
}
