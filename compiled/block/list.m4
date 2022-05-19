    __compiled_word("LIST", cw_list, 0)
    /*
     * : list
     *     dup scr !
     *     block
     *     dup 1024 + swap
     *     do i @ emit loop
     * ;
     */
    _compile_pr(pr_dup);
    _compile_pr(pr_scr);
    _compile_pr(pr_store);
    _compile_pr(pr_dup);
    _compile_pr(pr_buffer);
    _compile_pr(pr_read_block);
    _compile_pr(pr_dup);
    _compile_literal(_from_ptr(&e[ea_buffer_size]));
    _compile_pr(pr_fetch);
    _compile_pr(pr_plus);
    _compile_pr(pr_swap);
    _compile_do();
    _compile_pr(pr_i);
    _compile_pr(pr_fetch);
    _compile_pr(pr_emit);
    _compile_loop();
    _compile_pr(op_exit);
