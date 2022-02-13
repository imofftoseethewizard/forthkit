_primitive(pr_variable) {

    _store_word_name();

    /* Indicates that this word can be inlined during compilation. */
    _word_header(c_value);

    /* Compile the word. It just puts a literal on the stack. */
    _compile_pr(op_literal);
    _store_data(_from_ptr((cell *)here + 2));
    _compile_pr(op_exit);
    here += sizeof(cell);

    _next();
}
_define_parsing_primitive("VARIABLE", pr_variable);
