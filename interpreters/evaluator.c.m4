include(__preamble)dnl
include(__execution_model)dnl
include(__evaluator_primitives)dnl
include(__compiled_words)dnl

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>

#include "evaluator.h"

char *store_counted_string(const char *s, char *dp);
int write_image_block(cell length, cell addr, char *data, FILE *file);

void
init_evaluator(
    cell *e,
    cell buffer_count,
    cell buffer_size,
    cell evaluator_size,
    cell fiber_count,
    cell fiber_stack_size,
    cell pad_buffer_size,
    cell parameter_stack_size,
    cell return_stack_size,
    cell source_size,
    cell task_count,
    cell word_buffer_size)
{
    e[ea_buffer_count]         = buffer_count;
    e[ea_buffer_size]          = buffer_size;
    e[ea_fiber_count]          = fiber_count;
    e[ea_fiber_stack_size]     = fiber_stack_size;
    e[ea_pad_buffer_size]      = pad_buffer_size;
    e[ea_parameter_stack_size] = parameter_stack_size;
    e[ea_return_stack_size]    = return_stack_size;
    e[ea_size]                 = evaluator_size;
    e[ea_source_size]          = source_size;
    e[ea_task_count]           = task_count;
    e[ea_word_buffer_size]     = word_buffer_size;

    /* signals to evalute() that the evaluator's memory is uninitialized */
    e[ea_top] = 0;
}

int
evaluate(cell *evaluator, const char *source, int storage_fd)
{
    __declare_primitives()dnl

    int result = 0;

    register cell *e = evaluator;

    register char *top;
    register cell *tp;    /* current task */
    register cell *fp;    /* current fiber */

    register cell *fp0;
    register cell *rp0;
    register cell *sp0;

    register char *dp;
    register cell *sp;

    register cell *ip;
    register cell *rp;
    register cell *rp_stop;
    register number steps;

    __declare_evaluator_variables()

    ifdef(`__include_bootstrap', `include(`./bootstrap.c.m4')')dnl

    _debug("interpreting source '%s'\n", source);

    /* copy source into evaluator memory */

    memcpy(_to_ptr(e[ea_source_addr]), source, e[ea_source_len] = strlen(source));
    e[ea_source_idx] = 0;

    /* push new fiber for the interpreter task onto fiber stack */

    fp = fp0 = _to_ptr(e[ea_fp0]);
    *--fp = _primary_fiber;

    _load_fiber_state();

    rp = rp_stop = rp0;
    *--rp = 0;
    ip = _to_ptr(tp[ta_interpret]);

    steps = -1;

    _save_fiber_state();

    __implement_evaluator_core() dnl

    _debug("done with run: result: %d\n", result);
    _print_stack();

    return result;
}

char *
store_counted_string(const char *s, char *dp)
{
    cell n = strlen(s);

    dp = (char *)_align(dp);

    *(length_type *)dp = n;

    strncpy((char *)((length_type *)dp + 1), s, n);

    return dp + sizeof(cell) + n + 1;
}

int
write_image_block(cell length, cell addr, char *data, FILE *file)
{
    return (sizeof(cell)    == fwrite(&length, 1, sizeof(cell), file)
            && sizeof(cell) == fwrite(&addr, 1, sizeof(cell), file)
            && length       == fwrite(data, 1, length, file));
}

__discard_all_diversions()dnl
