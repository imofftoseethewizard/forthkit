_primitive(pr_do_create) {

    /* Indicates that this word can be inlined during compilation. */
    _word_header(c_inline);

    /* Compile the word. It just puts a literal on the stack. */
    _compile_pr(op_literal);
    _store_data(*sp++);
    _compile_pr(op_exit);

    _next();
}
_define_parsing_primitive("CREATE", pr_do_create);
