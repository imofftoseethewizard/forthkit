
    /* ' ( -- addr ) "tick"

        Used in the form:

        |  '  <name>

        addr is the compilation address of <name>.  An error
        condition exists if <name> is not found in the currently
        active search order.

        |  : '
        |    32 word find
        |    0= if
        |        err_undefined_word <abort>
        |    then
        |  ;
     */

    __compiled_word("'", cw_tick, 0)

    _compile_literal(32);
    _compile_cw(cw_word);
    _compile_pr(pr_find);

    _compile_pr(pr_zero_eq);
    _compile_if();

    _compile_literal(err_undefined_word);
    _compile_pr(op_abort);

    _compile_then();

    _compile_pr(op_exit);
