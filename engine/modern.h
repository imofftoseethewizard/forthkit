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

struct engine {
    int size;
    void *user;

    cell *data_stack;
    cell *sp;
    cell *sp0;

    cell **return_stack;
    cell **rp;
    cell **rp0;

    void **ip;

    char *here;
    char *top;

    int state;
    int base;

    cell *context;
    cell *current;

    const char *source;
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
        + DATA_STACK_SIZE  * sizeof(cell)
        + DATA_AREA_SIZE
        ];
};

extern int init_engine(struct engine *e);
extern int run_engine(struct engine *e);
extern int engine_interpret_source(struct engine *e, const char *source);
extern void reset_engine_execution_state(struct engine *e);
