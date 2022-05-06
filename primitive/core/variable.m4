__primitive(pr_variable)  
{

    _store_word_name();

    /* Indicates that this word can be inlined during compilation. */
    _word_header(c_value);

    /* Compile the word. It just puts a literal on the stack. */
    _compile_pr(op_literal);
    _store_data(_from_ptr((cell *)dp + 2));
    _compile_pr(op_exit);
    dp += sizeof(cell);

}
__end
__define_parsing_primitive("VARIABLE", pr_variable);
