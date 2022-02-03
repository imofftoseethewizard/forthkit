#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* #include "../threading/direct.c" */
/* #include "../threading/direct-relocatable.c" */
#include "../threading/direct-relocatable-traced.c"
/* #include "../threading/direct-traced.c" */
/* #include "../threading/subroutine.c" */

#include "../primitive/preamble.c"

#include "modern.h"
#include "log.h"

char *store_counted_string(const char *s, char *here);

void
init_engine(cell *e, cell size)
{
    cell *rp = e + (engine_attribute_count + SOURCE_SIZE + RETURN_STACK_SIZE);
    cell *sp = rp + PARAMETER_STACK_SIZE;
    cell *top = e + size / sizeof(cell);

    e[ea_size]        = size;

    /* registers */
    e[ea_ip]          = 0;
    e[ea_rp]          = _from_native_ptr(rp);
    e[ea_sp]          = _from_native_ptr(sp);
    e[ea_here]        = e[ea_sp];

    /* internal state */
    e[ea_base]        = 10;
    e[ea_context]     = 0;
    e[ea_current]     = 0;
    e[ea_data]        = e[ea_here];
    e[ea_rp0]         = e[ea_rp];
    e[ea_source_idx]  = 0;
    e[ea_source_len]  = 0;
    e[ea_sp0]         = e[ea_sp];
    e[ea_state]       = 0;

    /* external_state */

    e[ea_interpret]   = 0;
    e[ea_source_addr] = _from_native_ptr(&e[engine_attribute_count]);
    e[ea_top]         = _from_native_ptr(top);

    /* e[ea_] = 0; */
}

void
reset_engine_execution_state(cell *e)
{
    e[ea_sp] = e[ea_sp0];
    e[ea_rp] = e[ea_rp0];
    e[ea_ip] = 0;
}

int
run_engine(cell *engine) {

    /* These are the most commonly referenced variables. */
    register cell *e  = engine;
    register cell *ip = _to_native_ptr(e[ea_ip]);
    register cell *sp = _to_native_ptr(e[ea_sp]);
    register cell *rp = _to_native_ptr(e[ea_rp]);

    /* These are generally useful to have, but probably not worth putting
       in a register.
     */
    char *here = (char *)_to_native_ptr(e[ea_here]);
    cell *rp0  = (cell *)_to_native_ptr(e[ea_rp0]);
    cell *sp0  = (cell *)_to_native_ptr(e[ea_sp0]);

    /* Not currently used, but reserved for uncaught exceptions. */
    cell result = 0;

    /* Temporary variables for use in primitives (swap, roll, etc). */
    cell tmp0, tmp1;

    /* The label `__first` must appear before any labels used as a target
       of the `next()` macro immediately below. That uses the `__first` and
       `__last` labels to distinguish primitives from compiled words.
    */
  __first:

    #include "../primitive/op/abort.c"
    #include "../primitive/op/branch.c"
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

    _dispatch();

  __last:

    /* Store state back in the engine structure. */
    e[ea_ip]   = _from_native_ptr(ip);
    e[ea_sp]   = _from_native_ptr(sp);
    e[ea_rp]   = _from_native_ptr(rp);
    e[ea_here] = _from_native_ptr(here);

    _debug("done with run\n");
    return result;
}

int
engine_interpret_source(cell *e, const char *source)
{
    _debug("interpreting source '%s'\n", source);

    // TODO
    _debug("interpret %lx\n", (long)e[ea_interpret]);

    cell i = strlen(source);
    e[ea_source_len] = i;
    memcpy(_to_native_ptr(e[ea_source_addr]), source, i);

    e[ea_rp] = e[ea_rp0];
    e[ea_rp] -= sizeof(cell);
    *_to_native_ptr(e[ea_rp]) = 0;
    e[ea_ip] = e[ea_interpret];

    for (cell p = e[ea_interpret]; p < e[ea_here]; p += sizeof(cell))
        _debug("%lx: %lx\n", (long)_to_native_ptr(p), (long)*_to_native_ptr(p));

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
    _debug("engine: %lx top: %lx\n", (long)engine, (long)((char *)engine + sizeof(engine)));
    /* Clears structure. */
    init_engine(engine, sizeof(engine)/sizeof(cell));
    _debug("engine initialized.\n");

    /* Bootstrap. */
    run_engine(engine);
    _debug("bootstrap complete.\n");

    /* Actually do something. */
    exit(engine_interpret_source(engine, "65 EMIT"));
//    exit(engine_interpret_source(engine, argv[1]));
}
