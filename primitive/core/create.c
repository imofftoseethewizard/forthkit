_primitive(pr_do_create) {

    _print_stack();
    _debug("create: ");
    /* Indicates that this word can be inlined during compilation. */
    _word_header(c_inline);
    _debug("word_header ");

    /* Compile the word. It just puts a literal on the stack. */
    _compile_pr(op_literal);
    _debug("op_literal ");


    /* here + 2 is the location immediately after the exit below. */
    _store_data((cell *)here + 2);
    _debug("_store_data ");

    _compile_pr(op_exit);
    _debug("op_exit\n");

    _print_stack();
    _next();
}
_define_parsing_primitive("CREATE", pr_do_create);
