
    /* LOAD ( u -- )

       The contents of >IN and BLK , which locate the current input
       stream, are saved.  The input stream is then redirected to
       the beginning of screen u by setting >IN to zero and BLK to
       u.  The screen is then interpreted.  If interpretation from
       screen u is not terminated explicitly it will be terminated
       when the input stream is exhausted and then the contents of
       >IN and BLK will be restored.  An error condition exists if
       u is zero.

       |   : load
       |       dup 0= if err_invalid_block_number <abort> then
       |       >in @ >r
       |       blk @ >r
       |       0 >in !
       |       dup blk !
       |       block drop
       |       interpret
       |       r> blk !
       |       r> >in !
       |   ;

     */
    __compiled_word("LOAD", cw_load, 0)

    _compile_pr(pr_dup);
    _compile_pr(pr_zero_eq);
    _compile_if();
    _compile_literal(err_invalid_block_number);
    _compile_pr(op_abort);
    _compile_then();

    _compile_literal(_from_ptr(&e[ea_source_addr]));
    _compile_pr(pr_fetch);
    _compile_pr(pr_to_r);

    _compile_literal(_from_ptr(&e[ea_source_len]));
    _compile_pr(pr_fetch);
    _compile_pr(pr_to_r);

    _compile_pr(pr_to_in);
    _compile_pr(pr_fetch);
    _compile_pr(pr_to_r);

    _compile_pr(pr_blk);
    _compile_pr(pr_fetch);
    _compile_pr(pr_to_r);

    _compile_pr(pr_dup);
    _compile_pr(pr_blk);
    _compile_pr(pr_store);

    _compile_literal(0);
    _compile_pr(pr_to_in);
    _compile_pr(pr_store);

    _compile_pr(pr_dup);
    _compile_pr(pr_buffer);
    _compile_pr(pr_read_block);

    _compile_literal(_from_ptr(&e[ea_source_addr]));
    _compile_pr(pr_store);

    _compile_literal(_from_ptr(&e[ea_buffer_size]));
    _compile_pr(pr_fetch);
    _compile_literal(_from_ptr(&e[ea_source_len]));
    _compile_pr(pr_store);

    _store_data(tp[ta_interpret]);

    _compile_pr(pr_r_from);
    _compile_pr(pr_blk);
    _compile_pr(pr_store);

    _compile_pr(pr_r_from);
    _compile_pr(pr_to_in);
    _compile_pr(pr_store);

    _compile_pr(pr_r_from);
    _compile_literal(_from_ptr(&e[ea_source_len]));
    _compile_pr(pr_store);

    _compile_pr(pr_r_from);
    _compile_literal(_from_ptr(&e[ea_source_addr]));
    _compile_pr(pr_store);

    _compile_pr(op_exit);
