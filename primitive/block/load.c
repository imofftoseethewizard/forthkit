/* : load
       >in @ >r
       blk @ >r
       0 >in !
       dup blk !
       block drop
       interpret
       r> blk !
       r> >in !
   ;
 */
_compiled_word("LOAD", 0) {
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
    _compile_literal(BUFFER_SIZE);
    _compile_literal(_from_ptr(&e[ea_source_len]));
    _compile_pr(pr_store);
    _store_data(e[ea_interpret]);
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
}
