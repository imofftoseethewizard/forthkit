parsing_primitive pr_variable()
{
    _store_word_name();

    /* Indicates that this word can be inlined during compilation. */
    _word_header(c_inline2);

    _compile_variable();

    _end_define_word();

    _check_dictionary_bounds();
}
