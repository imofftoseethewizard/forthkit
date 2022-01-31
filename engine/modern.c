#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "modern.h"
#include "log.h"

char *store_counted_string(const char *s, char *here);

void
print_stack(cell *sp0, cell *sp)
{
    _debug("stack: ");
#if VERBOSE
    while (sp < sp0)
        _debug("%lx ", *--sp0);
#endif
    _debug("\n");
}

int
init_engine(struct engine *e)
{
    char *data_end = e->data + sizeof(e->data);

    /* Ensure stacks have cell-aligned addresses. */
    data_end -= (cell)data_end & (sizeof(cell) - 1);

    e->return_stack = (cell **)data_end - RETURN_STACK_SIZE;
    e->rp = e->rp0 = e->return_stack + RETURN_STACK_SIZE;

    e->data_stack = (cell *)e->return_stack - DATA_STACK_SIZE;
    e->sp = e->sp0 = e->data_stack + DATA_STACK_SIZE;

    e->top = (char *)e->data_stack;

    e->ip = 0;

    e->here = e->data;

    e->state = 0;
    e->base = 10;

    e->context = 0;
    e->current = 0;

    e->source = NULL;
    e->source_len = 0;
    e->source_idx = 0;

    e->interpret = 0;

    e->result = 0;

    /*e->cp = e->cp0 = e->context_stack;*/
    /* e->t_sp = e->t_sp0 = e->data_stack; */
}

void
reset_engine_execution_state(struct engine *e)
{
    e->sp = e->sp0;
    e->rp = e->rp0;
    /*
    e->t_sp = e->t_sp0;
    e->cp = e->cp0;
    */
    e->ip = 0;
}

int
run_engine(struct engine *engine)
{
    /* These are the most commonly referenced variables. */
    register struct engine *e = engine;
    register void **ip  = e->ip;
    register cell *sp   = e->sp;
    register cell **rp  = e->rp;

    char *here          = e->here;
    char *top           = e->top;

    cell **rp0          = e->rp0;
    cell *sp0           = e->sp0;

    /* currently unused
    cell *t_sp = e->t_sp;
    cell **cp0          = e->cp0;
    cell **cp           = e->cp;
    cell *t_sp0         = e->t_sp0;
    */

    const char *source  = e->source;
    int source_len      = e->source_len;
    int source_idx      = e->source_idx;

    cell *current       = e->current;
    cell *context       = e->context;
    cell state          = e->state;
    cell base           = e->base;

    int result          = e->result;
    void **operators    = e->operators;

    void *interpret     = e->interpret;

    /* Below are some temporary variables for use in primitives. */

    cell tmp0, tmp1;

    /* The label `__first` must appear before any labels used as a target
       of the `next()` macro immediately below. That uses the `__first` and
       `__last` labels to distinguish primitives from compiled words.
    */
  __first:
    /* #include "../threading/direct.c" */
    /* #include "../threading/direct-relocatable.c" */
    /* #include "../threading/direct-traced.c" */
    #include "../threading/subroutine.c"

    #include "../primitive/preamble.c"

    #include "../primitive/op/abort.c"
    #include "../primitive/op/branch.c"
    #include "../primitive/op/call.c"
    #include "../primitive/op/exit.c"
    #include "../primitive/op/jump.c"
    #include "../primitive/op/literal.c"

    /* Prerequisites for bootstrap */
    #include "../primitive/core/abort.c"
    #include "../primitive/core/align.c"
    #include "../primitive/core/count.c"
    #include "../primitive/core/create.c"
    #include "../primitive/core/drop.c"
    #include "../primitive/core/execute.c"
    #include "../primitive/core/fetch.c"
    #include "../primitive/core/find.c"
    #include "../primitive/core/literal.c"
    #include "../primitive/core/nip.c"
    #include "../primitive/core/or.c"
    #include "../primitive/core/over.c"
    #include "../primitive/core/q_dup.c"
    #include "../primitive/core/state.c"
    #include "../primitive/core/store_compiled.c"
    #include "../primitive/core/store_data.c"
    #include "../primitive/core/swap.c"
    #include "../primitive/core/to_number.c"
    #include "../primitive/core/word.c"
    #include "../primitive/core/zero_eq.c"
    #include "../primitive/core/zero_gt.c"

    #include "../primitive/core/compile_begin.c"
    #include "../primitive/core/compile_else.c"
    #include "../primitive/core/compile_if.c"
    #include "../primitive/core/compile_then.c"
    #include "../primitive/core/compile_repeat.c"
    #include "../primitive/core/compile_while.c"

    #include "../bootstrap/interpret.c"

    #include "../primitive/posix/emit.c"
    /* #include "../primitive/posix/key.c" */

    /* #include "../primitive/core/posix/readline/refill.c" */
    /* #include "../primitive/core/immediate.c" */

    context = current;

    _dispatch();

  __last:

    /* Store state back in the engine structure. */

    e->ip        = ip;
    e->sp        = sp;
    e->rp        = rp;

    e->here      = here;

    e->rp0       = rp0;
    e->sp0       = sp0;

    e->source_idx     = source_idx;

    e->current   = current;
    e->context   = context;
    e->state     = state;
    e->base      = base;

    e->result    = result;
    e->interpret = interpret;

    /* e->t_sp      = t_sp; */
    /* e->cp0       = cp0; */
    /* e->cp        = cp; */
    /* e->t_sp0     = t_sp0; */
    _debug("done with run\n");
    return result;
}

int
engine_interpret_source(struct engine *e, const char *source)
{
    _debug("interpreting source '%s'\n", source);

    _debug("interpret %lx \n", (cell)e->interpret);

    e->source = source;
    e->source_len = strlen(source);

    e->rp = e->rp0;
    *--e->rp = 0;
    e->ip = e->interpret;

    /* for (cell *p = (cell *)e->interpret; p < (cell *)e->here; p++) */
    /*     _debug("%lx: %lx\n", (cell)p, *p); */

    return run_engine(e);
}

char *
store_counted_string(const char *s, char *here)
{
    cell n = strlen(s);

    here = (char *)_align(here);

    *(length_type *)here = n;

    strncpy((char *)((length_type *)here + 1), s, n);

    return here + sizeof(cell) + n + 1;
}

struct engine m;

int
main(int argc, char *argv[])
{
    /* Clears structure. */
    init_engine(&m);
    _debug("engine initialized.\n");

    /* Bootstrap. */
    run_engine(&m);
    _debug("bootstrap complete.\n");

    /* Actually do something. */
    exit(engine_interpret_source(&m, argv[1]));
}
