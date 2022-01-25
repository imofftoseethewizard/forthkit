define_parsing_primitive("CREATE", &&pr_do_create);

if (0)
  {
  pr_do_create:

    /* Indicates that this word can be inlined during compilation. */
    _word_header(c_inline);

    /* Compile the word. It just puts a literal on the stack. */
    *here++ = (cell)&&op_literal;

    /* here + 2 is the location immediately after the exit below. */
    *here++ = (cell)(here + 2);
    *here++ = (cell)&&op_exit;

    _next();
  }
