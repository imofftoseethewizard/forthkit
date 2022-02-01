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

void
print_return_stack(cell **rp0, cell **rp)
{
    _debug("return stack: ");
#if VERBOSE
    while (rp < rp0)
        _debug("%lx ", (cell)*--rp0);
#endif
    _debug("\n");
}

void
init_engine(cell *data, cell size)
{
    data[ea_size]        = size;

    /* registers */
    data[ea_ip]          = 0;
    data[ea_rp]          = (cell)data + (engine_attribute_count + SOURCE_SIZE + RETURN_STACK_SIZE) * sizeof(cell) ;
    data[ea_sp]          = (cell)((cell *)data[ea_rp] + PARAMETER_STACK_SIZE);
    data[ea_here]        = data[ea_sp];

    /* internal state */
    data[ea_base]        = 10;
    data[ea_context]     = 0;
    data[ea_current]     = 0;
    data[ea_data]        = data[ea_here];
    data[ea_rp0]         = data[ea_rp];
    data[ea_source_idx]  = 0;
    data[ea_source_len]  = 0;
    data[ea_sp0]         = data[ea_sp];
    data[ea_state]       = 0;

    /* external_state */

    data[ea_interpret]   = 0;
    data[ea_source_addr] = engine_attribute_count;
    data[ea_top]         = (cell)((char *)data + ea_size * sizeof(cell));

    /* data[ea_] = 0; */
}

void
reset_engine_execution_state(cell *e)
{
    e[ea_sp] = e[ea_sp0];
    e[ea_rp] = e[ea_rp0];
    e[ea_ip] = 0;
}

int
run_engine(cell *engine)
{
    /* These are the most commonly referenced variables. */
    register cell *e   = engine;
    register cell *ip  = (cell *)e[ea_ip];
    register cell *sp  = (cell *)e[ea_sp];
    register cell **rp = (cell **)e[ea_rp];

    /* These are generally useful to have, but probably not worth putting
       in a register.
     */
    char *here = (char *)e[ea_here];
    cell **rp0 = (cell **)e[ea_rp0];
    cell *sp0  = (cell *)e[ea_sp0];

    /* Not currently used, but reserved for uncaught exceptions. */
    cell result = 0;

    /* Temporary variables for use in primitives (swap, roll, etc). */
    cell tmp0, tmp1;

    /* The label `__first` must appear before any labels used as a target
       of the `next()` macro immediately below. That uses the `__first` and
       `__last` labels to distinguish primitives from compiled words.
    */
  __first:
    /* #include "../threading/direct.c" */
    #include "../threading/direct-relocatable.c"
    /* #include "../threading/direct-relocatable-traced.c" */
    /* #include "../threading/direct-traced.c" */

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
    /* End of bootstrap */

    #include "../primitive/posix/emit.c"
    /* #include "../primitive/posix/key.c" */

    /* #include "../primitive/core/posix/readline/refill.c" */
    /* #include "../primitive/core/immediate.c" */

    /* The first run will have context == 0. The preamble detects that and
       defines primitives and the bootstrap interpreter.
     */
    if (!e[ea_context])
        e[ea_context] = e[ea_current];

    _next();

  __last:

    /* Store state back in the engine structure. */
    e[ea_ip]   = (cell)ip;
    e[ea_sp]   = (cell)sp;
    e[ea_rp]   = (cell)rp;
    e[ea_here] = (cell)here;

    _debug("done with run\n");
    return result;
}

int
engine_interpret_source(cell *e, const char *source)
{
    _debug("interpreting source '%s'\n", source);

    // TODO
    _debug("interpret %lx\n", e[ea_interpret]);

    cell i = strlen(source);
    e[ea_source_len] = i;
    memcpy(&e[e[ea_source_addr]], source, i);

    e[ea_rp] = e[ea_rp0];
    e[ea_rp] -= sizeof(cell);
    *(cell *)e[ea_rp] = 0;
    _debug("engine_interpret_source: rp: %lx *rp: %lx\n", e[ea_rp], *(cell *)e[ea_rp]);
    e[ea_ip] = e[ea_interpret];

    for (cell p = e[ea_interpret]; p < e[ea_here]; p += sizeof(cell))
        _debug("%lx: %lx\n", p, *(cell *)p);

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

cell engine[1 << 16];

int
main(int argc, char *argv[])
{
    /* Clears structure. */
    init_engine(engine, sizeof(engine)/sizeof(cell));
    _debug("engine initialized.\n");

    /* Bootstrap. */
    run_engine(engine);
    _debug("bootstrap complete.\n");

    /* Actually do something. */
    exit(engine_interpret_source(engine, argv[1]));
}
