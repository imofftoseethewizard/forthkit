#define _compile_while() \
    do { _compile_pr(op_branch); _compile_jump_origin(); _swap(); } while(0)