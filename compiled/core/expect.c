_define_primitive("EXPECT", pr_expect);
/*
_compiled_word("EXPECT", cw_expect, 0) {
    _compile_pr(pr_dup);
    _compile_pr(pr_to_r);
    _compile_literal(0);
    _compile_do();
    _compile_pr(pr_key);
    _compile_pr(pr_dup);
    _compile_literal(10);
    _compile_pr(pr_eq);
    _compile_if();
    _compile_pr(pr_drop);
    _compile_literal(0);
    _compile_pr(pr_over);
    _compile_pr(pr_i);
    _compile_pr(pr_plus);
    _compile_pr(pr_c_store);
    _compile_pr(pr_leave);
    _compile_else();
    _compile_pr(pr_over);
    _compile_pr(pr_i);
    _compile_pr(pr_plus);
    _compile_pr(pr_c_store);
    _compile_then();
    _compile_loop();
    _compile_pr(pr_from_r);
    _compile_pr(pr_plus);
    _compile_literal(0);
    _compile_pr(pr_swap);
    _compile_pr(pr_c_store);
    _compile_pr(op_exit);
}
*/
