#include "config.h"

typedef unsigned CELL_TYPE cell;
typedef CELL_TYPE number;
typedef CELL_TYPE cell_offset;

#define c_msb ((cell)1 << (sizeof(cell) * 8 - 1))

typedef LENGTH_TYPE length_type;

typedef DOUBLE_TYPE double_number;
typedef unsigned DOUBLE_TYPE double_cell;

#define _from_high_word(x) ((x) >> (sizeof(number)*8))
#define _from_low_word(x)  ((number)(x))
#define _to_high_word(x)   (((double_number)(x)) << (sizeof(number)*8))
#define _to_low_word(x)    ((double_number)(x))

enum operator_type {
    ot_abort,
    ot_branch,
    ot_call,
    ot_do,
    ot_exit,
    ot_jump,
    ot_literal,
    ot_loop,
    ot_plus_loop,

    /* must be last */
    operator_type_count
};

void *operators[operator_type_count];

enum engine_attribute {
    ea_size,
    ea_ip,
    ea_rp,
    ea_sp,
    ea_here,
    ea_base,
    ea_context,
    ea_current,
    ea_data,
    ea_forth,
    ea_rp0,
    ea_source_idx,
    ea_source_len,
    ea_sp0,
    ea_state,
    ea_interpret,
    ea_source_addr,
    ea_blk,
    ea_buffers,
    ea_next_buffer,
    ea_scr,

    /* must be last */
    engine_attribute_count
};

enum compiled_words {
    cw_79_standard,
    cw_block,
    cw_bracket_compile,
    cw_forget,
    cw_list,
    cw_load,
    cw_num_s,
    cw_query,
    cw_question_mark,
    cw_space,
    cw_spaces,
    cw_tick,
    cw_word
};

extern void init_engine(cell *e, unsigned long size);
extern int evaluate(cell *e, const char *source, int storage_fd);
extern void reset_execution_state(cell *e);

/* switched execution case tokens */

enum pr_token {
    op_abort_token = 1,
    op_branch_token,
    op_does_token,
    op_do_token,
    op_exit_token,
    op_jump_token,
    op_literal_token,
    op_loop_token,
    op_plus_loop_token,
    pr_abort_token,
    pr_abs_token,
    pr_align_token,
    pr_allot_token,
    pr_and_token,
    pr_base_token,
    pr_blk_token,
    pr_buffer_token,
    pr_c_comma_token,
    pr_c_fetch_token,
    pr_c_move_token,
    pr_colon_token,
    pr_compile_begin_token,
    pr_compile_do_token,
    pr_compile_else_token,
    pr_compile_if_token,
    pr_compile_loop_token,
    pr_compile_plus_loop_token,
    pr_compile_repeat_token,
    pr_compile_then_token,
    pr_compile_token,
    pr_compile_until_token,
    pr_compile_while_token,
    pr_constant_token,
    pr_context_token,
    pr_convert_token,
    pr_count_token,
    pr_create_token,
    pr_cr_token,
    pr_c_store_token,
    pr_current_token,
    pr_dash_trailing_token,
    pr_decimal_token,
    pr_definitions_token,
    pr_depth_token,
    pr_div_mod_token,
    pr_div_token,
    pr_d_lt_token,
    pr_d_negate_token,
    pr_do_does_token,
    pr_does_token,
    pr_dot_quote_token,
    pr_dot_token,
    pr_d_plus_token,
    pr_drop_token,
    pr_dup_token,
    pr_emit_token,
    pr_empty_buffers_token,
    pr_eq_token,
    pr_execute_token,
    pr_expect_token,
    pr_fetch_token,
    pr_fill_token,
    pr_find_token,
    pr_forth_token,
    pr_gt_token,
    pr_here_token,
    pr_hold_token,
    pr_immediate_token,
    pr_i_token,
    pr_j_token,
    pr_key_token,
    pr_leave_token,
    pr_left_bracket_token,
    pr_literal_token,
    pr_lshift_token,
    pr_lt_token,
    pr_max_token,
    pr_min_token,
    pr_minus_token,
    pr_mod_token,
    pr_move_token,
    pr_negate_token,
    pr_not_token,
    pr_num_end_token,
    pr_num_start_token,
    pr_num_token,
    pr_one_minus_token,
    pr_one_plus_token,
    pr_or_token,
    pr_over_token,
    pr_paren_token,
    pr_pick_token,
    pr_plus_store_token,
    pr_plus_token,
    pr_q_dup_token,
    pr_quit_token,
    pr_read_block_token,
    pr_r_fetch_token,
    pr_r_from_token,
    pr_right_bracket_token,
    pr_roll_token,
    pr_rot_token,
    pr_rshift_token,
    pr_save_buffers_token,
    pr_scr_token,
    pr_semicolon_token,
    pr_sign_token,
    pr_state_token,
    pr_store_compiled_token,
    pr_store_data_token,
    pr_store_token,
    pr_swap_token,
    pr_times_div_mod_token,
    pr_times_div_token,
    pr_times_token,
    pr_to_in_token,
    pr_token,
    pr_token_count,
    pr_to_number_token,
    pr_to_r_token,
    pr_two_minus_token,
    pr_two_plus_token,
    pr_type_token,
    pr_u_div_mod_token,
    pr_u_dot_token,
    pr_u_lt_token,
    pr_update_token,
    pr_u_times_token,
    pr_variable_token,
    pr_word_token,
    pr_xor_token,
    pr_zero_eq_token,
    pr_zero_gt_token,
    pr_zero_lt_token
};
