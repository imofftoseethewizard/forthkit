#include "config.h"

typedef CELL_TYPE cell;

typedef LENGTH_TYPE length_type;

typedef void (*native_word)(void);

enum operator_type {
    ot_abort,
    ot_branch,
    ot_call,
    ot_exit,
    ot_jump,
    ot_literal,
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
    ea_rp0,
    ea_source_idx,
    ea_source_len,
    ea_sp0,
    ea_state,
    ea_interpret,
    ea_result,
    ea_source_addr,
    ea_top,
    engine_attribute_count
};

extern void init_engine(cell *e, cell size);
extern int run_engine(cell *e);
extern int engine_interpret_source(cell *e, const char *source);
extern void reset_engine_execution_state(cell *e);
