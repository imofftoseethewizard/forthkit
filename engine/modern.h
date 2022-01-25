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
     count_operator_types
};

struct stack_machine {
     cell **cp0;
     cell **cp;
     cell **rp0;
     cell *sp0;
     cell *t_sp0;

     void **ip;
     char *here;
     cell **rp;
     cell *sp;
     cell *t_sp;

     int state;

     int buffer_len;
     char *point;

     char *token;
     int token_len;

     cell *current;
     cell *context;

     int result;

     void *operators[count_op_types];

     char buffer[TEXT_INPUT_BUFFER_SIZE+1];
     char data[DATA_SIZE];
     cell *context_stack[CONTEXT_STACK_SIZE];
     cell primary_stack[PRIMARY_STACK_SIZE];
     cell *return_stack[RETURN_STACK_SIZE];
};

extern int init_stack_machine(struct stack_machine *m);
extern int run_stack_machine(struct stack_machine *m);
extern void reset_stack_machine_execution_state(struct stack_machine *m);
