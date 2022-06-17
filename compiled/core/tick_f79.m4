
    /* ' ( -- addr ) "tick"

        Used in the form:
             '  <name>
        If  executing,  leave the parameter field address of the  next
        word accepted from the input stream.   If  compiling,  compile
        this  address  as a literal;  later execution will place  this
        value  on the stack.   An error condition exists if not  found
        after a search of the CONTEXT and FORTH vocabularies.   Within
        a  colon-definition  '  <name> is identical to [  '  <name>  ]
        LITERAL.

       |   : '
       |     32 word find ?dup if
       |         state @ if literal then
       |     else
       |         err_undefined_word <abort>
       |     then
       |   ; immediate
    */

    __compiled_word("'", cw_tick, c_immediate)

    _compile_literal(32);
    _compile_cw(cw_word);
    _compile_pr(pr_find);
    _compile_pr(pr_query_dup);
    _compile_if();

    _compile_pr(pr_state);
    _compile_pr(pr_fetch);
    _compile_if();
    _compile_pr(pr_literal);
    _compile_then();

    _compile_else();

    _compile_literal(err_undefined_word);
    _compile_pr(op_abort);

    _compile_then();

    _compile_pr(op_exit);
