__primitive(pr_word)
{
    /* Word buffer is on the top of the stack, delimiter is next. */
    register char *word_buffer = (char *)_to_ptr(*sp++);
    register char delimiter    = *sp++;
    register int word_idx      = 1;
    register char *source      = (char *)_to_ptr(e[ea_source_addr]);
    register cell source_len   = e[ea_source_len];
    register cell source_idx   = e[ea_source_idx];

    /* Skip leading delimiters. */
    while (source_idx < source_len
           && (source[source_idx] == delimiter || source[source_idx] < 32))
        source_idx++;

    /* Copy word from source to word buffer. */
    while (source_idx < source_len && word_idx < e[ea_word_buffer_size]
           && (source[source_idx] != delimiter && source[source_idx] > 32))
        word_buffer[word_idx++] = source[source_idx++];

    if (word_idx == 1) {
        _debug("word: <none>\n");
        *--sp = 0;

    } else {
        _debug("word: %.*s\n", (int)(word_idx - 1), word_buffer + sizeof(unsigned char));
        word_buffer[word_idx] = delimiter;
        *(unsigned char *)word_buffer = (unsigned char)(word_idx - 1);
        *--sp = _from_ptr(word_buffer);
    }

    e[ea_source_idx] = source_idx;
}
__end
__define_primitive("<word>", pr_word);
