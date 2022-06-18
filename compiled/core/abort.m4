
    /* ABORT

       Clear the data and return stacks, setting execution mode.
       End evaulation of current input source. Sets evaluator
       result to err_abort.
     */

    __compiled_word("ABORT", cw_abort, 0);
    _compile_literal(err_abort);
    _compile_pr(op_abort);
    /* no exit required */
