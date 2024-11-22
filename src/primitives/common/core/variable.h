#define _compile_variable()                                       \
    /* Compile the word. It just puts a literal on the stack. */  \
    _compile_pr(op_literal);                                      \
    _store_data(_from_ptr((cell *)dp + 2));                       \
                                                                  \
    _compile_pr(op_exit);                                         \
                                                                  \
    /* Leave space for the variable's value */                    \
    dp += sizeof(cell)
