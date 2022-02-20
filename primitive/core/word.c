_primitive(pr_word) {

    /* Delimiter is on the top of the stack. */
    register char delimiter    = *sp++;
    register char *word_buffer = (char *)_align(here);
    register int word_idx      = sizeof(length_type);
    register char *source      = (char *)_to_ptr(e[ea_source_addr]);
    register cell source_len   = e[ea_source_len];
    register cell source_idx   = e[ea_source_idx];

    /* Skip leading delimiters. */
    while (source_idx < source_len
           && (source[source_idx] == delimiter || source[source_idx] < 32))
        source_idx++;

    /* Copy word from source to word buffer. */
    while (source_idx < source_len && word_idx < MAX_WORD_LENGTH
           && (source[source_idx] != delimiter && source[source_idx] > 32))
        word_buffer[word_idx++] = source[source_idx++];

    if (word_idx == sizeof(length_type)) {
        _debug("word: <none>\n");
        *--sp = 0;

    } else {
        _debug("word: %.*s\n", (int)(word_idx - sizeof(length_type)), word_buffer + sizeof(length_type));
        *(length_type *)word_buffer = (length_type)(word_idx - sizeof(length_type));
        *--sp = _from_ptr(word_buffer);
    }

    e[ea_source_idx] = source_idx;

    _next();
}
_define_primitive("WORD", pr_word);
