
    /* ['] ( -- addr ) "bracket-tick"

       Used in the form:

       |   ['] <name>

       Compiles the compilation address addr of <name> as a
       literal.  When the colon definition is later executed addr
       is left on the stack.  An error condition exists if <name>
       is not found in the currently active search order.

       |   : ['] ' LITERAL ; IMMEDIATE

     */

    __compiled_word("[']", cw_bracket_tick, c_immediate);
    _compile_cw(cw_tick);
    _compile_pr(pr_literal);
    _compile_pr(op_exit);
