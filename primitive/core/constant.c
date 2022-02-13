_primitive(pr_constant) {

    _store_word_name();

    /* Indicates that this word can be inlined as 2 cells during compilation. */
    _word_header(c_value);

    /* Compile the word. It just puts a literal on the stack. */
    _compile_pr(op_literal);
    _store_data(*sp++);
    _compile_pr(op_exit);

    _next();
}
_define_parsing_primitive("CONSTANT", pr_constant);
