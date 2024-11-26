pr_variable:
{
    _store_word_name();
    _word_header(0);

    _compile_pw(op_do_var);
    _store_data(0);

    _end_define_word();

    _check_dictionary_bounds();
}
