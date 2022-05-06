__primitive(pr_create)  
{

    _store_word_name();

    /* Indicates that this word can be inlined during compilation. */
    _word_header(c_value);

    /* Compile the word. It just puts a literal on the stack. */
    _compile_pr(op_literal);

    /* dp + 2 is the location immediately after the exit below. */
    _store_data(_from_ptr((cell *)dp + 2));
    _compile_pr(op_exit);

}
__end
__define_parsing_primitive("CREATE", pr_create);
