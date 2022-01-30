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
    ea_interpret,
    ea_result,
    ea_source_addr,
    engine_attribute_count
};

struct engine {
    int size;
    void *user;

    cell *parameter_stack;
    cell *sp;
    cell *sp0; //

    cell **return_stack;
    cell **rp;
    cell **rp0; //

    void **ip;

    char *here; //
    char *top;

    cell state; //
    cell base; ///

    cell *context; //
    cell *current; //

    const char *source; //
    int source_len;
    int source_idx; /* >in */

    void *interpret;
    void *operators[operator_type_count];

    int result;

    /* Currently unused.
    cell *t_sp;
    cell *t_sp0;
    cell **cp0;
    cell **cp;
    cell **context_stack;
    */

    char data[
        RETURN_STACK_SIZE * sizeof(cell)
        + PARAMETER_STACK_SIZE  * sizeof(cell)
        + DATA_AREA_SIZE
        ];
};

extern int init_engine(struct engine *e);
extern int run_engine(struct engine *e);
extern int engine_interpret_source(struct engine *e, const char *source);
extern void reset_engine_execution_state(struct engine *e);
