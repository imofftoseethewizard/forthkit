#define _compile_2variable()                                       \
    /* Compile the word. It just puts a literal on the stack. */  \
    _compile_pr(op_literal);                                      \
    _store_data(_from_ptr((cell *)dp + 2));                       \
                                                                  \
    _compile_pr(op_exit);                                         \
                                                                  \
    /* Leave space for the variable's value */                    \
    dp += 2*sizeof(cell)

__primitive(pr_2variable)
{
    _store_word_name();

    /* Indicates that this word can be inlined during compilation. */
    _word_header(c_inline2);

    _compile_2variable();

    _end_define_word();

    _check_dictionary_bounds();
}
__end
__define_parsing_primitive("2VARIABLE", pr_2variable);