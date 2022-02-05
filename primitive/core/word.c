_primitive(pr_word) {

    /* Delimiter is on the top of the stack. */
    register char delimiter    = *sp++;
    register char *word_buffer;
    register int word_idx      = sizeof(length_type);
    register char *source      = (char *)_to_native_ptr(e[ea_source_addr]);
    register cell source_len   = e[ea_source_len];
    register cell source_idx   = e[ea_source_idx];

    if (e[ea_top])
        word_buffer = (char *)_to_native_ptr(e[ea_top]) - MAX_WORD_LENGTH;
    else
        /* The relocatable threading model allows cell sizes smaller than the machine word
           size. In that case, e[ea_top] will be zero when a full address space is
           available. For example, with CELL_TYPE short, the full address space is 64KB, or 2^15
           cells. When computing e[ea_top] using _from_native_ptr, the machine word-width result
           of (x) - e == 0x10000 will be truncated to 0x0. That case is explicitly handled here.
        */
        word_buffer = (char *)e + (1 << sizeof(cell)*8) - MAX_WORD_LENGTH;

    /* Skip leading delimiters. */
    while (source_idx < source_len && source[source_idx] == delimiter)
        source_idx++;

    /* Copy word from source to word buffer. */
    while (source_idx < source_len && word_idx < MAX_WORD_LENGTH
           && source[source_idx] != delimiter)
        word_buffer[word_idx++] = source[source_idx++];

    if (word_idx == sizeof(length_type)) {
        _debug("word: <none>\n");
        *--sp = 0;

    } else {
        _debug("word: %.*s\n", (int)(word_idx - sizeof(length_type)), word_buffer + sizeof(length_type));
        *(length_type *)word_buffer = (length_type)(word_idx - sizeof(length_type));
        *--sp = _from_native_ptr(word_buffer);
    }

    e[ea_source_idx] = source_idx;

    _next();
}
define_primitive("WORD", pr_word);
