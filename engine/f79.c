
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>

#include "../primitive/preamble-79.h"

#include "f79.h"
#include "log.h"

char *store_counted_string(const char *s, char *here);

void
init_engine(cell *e, unsigned long size)
{
    e[ea_size]    = size;
    e[ea_forth] = 0;
}

void
reset_execution_state(cell *e)
{
    e[ea_sp] = e[ea_sp0];
    e[ea_rp] = e[ea_rp0];
    e[ea_ip] = 0;
}

int
evaluate(cell *engine, const char *source)
{
    /* #include "../address/absolute.c" */
    #include "../address/relocatable.c"

    /* These are the most commonly referenced variables. */
    register cell *e = engine;
    register cell *ip;
    register cell *sp;
    register cell *rp;

    if (e[ea_interpret]) {

        ip = _to_ptr(e[ea_ip]);
        sp = _to_ptr(e[ea_sp]);
        rp = _to_ptr(e[ea_rp]);

    } else {

        rp = e + (engine_attribute_count + SOURCE_SIZE + RETURN_STACK_SIZE);
        sp = rp + PARAMETER_STACK_SIZE;

        /* registers */
        e[ea_ip]          = 0;
        e[ea_rp]          = _from_ptr(rp);
        e[ea_sp]          = _from_ptr(sp);
        e[ea_here]        = e[ea_sp];

        /* internal state */
        e[ea_base]        = 10;
        e[ea_context]     = 0;
        e[ea_current]     = ea_forth;
        e[ea_data]        = e[ea_here];
        e[ea_forth]       = 0;
        e[ea_rp0]         = e[ea_rp];
        e[ea_source_idx]  = 0;
        e[ea_source_len]  = 0;
        e[ea_sp0]         = e[ea_sp];
        e[ea_state]       = 0;

        /* external_state */
        e[ea_interpret]   = 0;
        e[ea_source_addr] = _from_ptr(&e[engine_attribute_count]);

        /* e[ea_] = 0; */
    }

    /* These are generally useful to have, but probably not worth putting
       in a register.
     */
    char *here = (char *)_to_ptr(e[ea_here]);
    cell *rp0  = (cell *)_to_ptr(e[ea_rp0]);
    cell *sp0  = (cell *)_to_ptr(e[ea_sp0]);

    /* Not currently used, but reserved for uncaught exceptions. */
    int result = 0;

    /* Temporary variables for use in primitives (swap, roll, etc). */
    cell tmp0, tmp1;

    /* The threading module must be included before any operators or
       primitives.
     */
    #include "../threading/direct.c"
    /* #include "../threading/subroutine.c" */

    #include "../primitive/op/abort.c"
    #include "../primitive/op/branch.c"
    #include "../primitive/op/do.c"
    #include "../primitive/op/exit.c"
    #include "../primitive/op/jump.c"
    #include "../primitive/op/literal.c"
    #include "../primitive/op/loop.c"
    #include "../primitive/op/plus_loop.c"

    /* Prerequisites for bootstrap */
    #include "../primitive/core/store_compiled.c"
    #include "../primitive/core/align.c"
    #include "../primitive/core/and.c"
    #include "../primitive/core/count.c"
    #include "../primitive/core/create.c"
    #include "../primitive/core/drop.c"
    #include "../primitive/core/dup.c"
    #include "../primitive/core/execute.c"
    #include "../primitive/core/fetch.c"
    #include "../primitive/core/find-79.c"
    #include "../primitive/core/literal.c"
    #include "../primitive/core/minus.c"
    #include "../primitive/core/or.c"
    #include "../primitive/core/over.c"
    #include "../primitive/core/q_dup.c"
    #include "../primitive/core/state.c"
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

    #include "../bootstrap/interpret-79.c"
    /* End of bootstrap */

    #include "../primitive/core/posix/emit.c"
    #include "../primitive/core/posix/key.c"

    #include "../primitive/core/abs.c"
    #include "../primitive/core/allot.c"
    #include "../primitive/core/base.c"
    #include "../primitive/core/c_fetch.c"
    #include "../primitive/core/c_move.c"
    #include "../primitive/core/c_store.c"
    #include "../primitive/core/colon.c"
    #include "../primitive/core/compile.c"
    #include "../primitive/core/compile_do.c"
    #include "../primitive/core/compile_loop.c"
    #include "../primitive/core/compile_plus_loop.c"
    #include "../primitive/core/constant.c"
    #include "../primitive/core/context.c"
    #include "../primitive/core/cr.c"
    #include "../primitive/core/current.c"
    #include "../primitive/core/decimal.c"
    #include "../primitive/core/definitions.c"
    #include "../primitive/core/depth.c"
    #include "../primitive/core/div.c"
    #include "../primitive/core/does.c"
    #include "../primitive/core/dot_quote.c"
    #include "../primitive/core/exit.c"
    #include "../primitive/core/fill.c"
    #include "../primitive/core/here.c"
    #include "../primitive/core/hold.c"
    #include "../primitive/core/i.c"
    #include "../primitive/core/immediate.c"
    #include "../primitive/core/j.c"
    #include "../primitive/core/leave.c"
    #include "../primitive/core/left_bracket.c"
    #include "../primitive/core/max.c"
    #include "../primitive/core/min.c"
    #include "../primitive/core/mod.c"
    #include "../primitive/core/move.c"
    #include "../primitive/core/negate.c"
    #include "../primitive/core/not.c"
    #include "../primitive/core/num.c"
    #include "../primitive/core/num_end.c"
    #include "../primitive/core/num_start.c"
    #include "../primitive/core/one_minus.c"
    #include "../primitive/core/one_plus.c"
    /* #include "../primitive/core/paren.c" */
    #include "../primitive/core/plus.c"
    #include "../primitive/core/plus_store.c"
    #include "../primitive/core/posix/type.c"
    #include "../primitive/core/quit.c"
    #include "../primitive/core/r_fetch.c"
    #include "../primitive/core/r_from.c"
    #include "../primitive/core/right_bracket.c"
    #include "../primitive/core/semicolon.c"
    #include "../primitive/core/sign.c"
    #include "../primitive/core/store.c"
    #include "../primitive/core/times.c"
    #include "../primitive/core/times_div.c"
    #include "../primitive/core/to_r.c"
    #include "../primitive/core/two_minus.c"
    #include "../primitive/core/two_plus.c"
    #include "../primitive/core/variable.c"
    #include "../primitive/core/xor.c"
    #include "../primitive/core_ext/pick.c"
    /* #include "../primitive/core_ext/roll.c" */

    #include "../primitive/core/posix/dot.c"

    #include "../compiled/core/bracket_compile.c"
    #include "../compiled/core/num_s.c"
    /* #include "../compiled/core/tick_f79.c" */
    #include "../compiled/core/word.c"

    /* The first run will have context == 0. The preamble detects that and
       defines primitives and the bootstrap interpreter.
     */
    if (!e[ea_context])
        e[ea_context] = ea_forth;

    if (source) {
        _debug("interpreting source '%s'\n", source);

        memcpy(_to_ptr(e[ea_source_addr]), source, e[ea_source_len] = strlen(source));
        e[ea_source_idx] = 0;

        rp = rp0;
        *--rp = 0;
        ip = _to_ptr(e[ea_interpret]);
    }

    _dispatch();

    /* Store state back in the engine structure. */
    e[ea_ip]   = _from_ptr(ip);
    e[ea_sp]   = _from_ptr(sp);
    e[ea_rp]   = _from_ptr(rp);
    e[ea_here] = _from_ptr(here);

    _debug("done with run: result: %d\n", result);
    _print_stack();
    return result;
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

void
show_error(const char *message, const char *line, cell n) {
    fprintf(stderr, "%s:\n", message);
    fprintf(stderr, "%s\n", line);
    for (int i = 0; i < n; i++)
        putc(' ', stderr);
    putc('^', stderr);
    putc('\n', stderr);
}

cell engine[1 << 15];

int
main(int argc, char *argv[])
{
    int result;
    char *line;

    _debug("engine: %lx top: %lx\n", (long)engine, (long)((char *)engine + sizeof(engine)));

    /* Clears structure. */
    init_engine(engine, sizeof(engine));

    _debug("engine initialized.\n");

    printf("Forthkit FORTH-79\n");
    while (1) {
        line = readline(NULL);
        result = evaluate(engine, line);
        switch (result) {
        case 0:
            printf("ok\n");
            break;
        case -13:
            show_error("unrecognized word", line, engine[ea_source_idx]);
            break;
        case -39:
            show_error("unexpected end of input", line, engine[ea_source_idx]);
            break;
        default:
            fprintf(stderr, "unknown throw code: %ld\n", (long)result);
            show_error("error location", line, engine[ea_source_idx]);
            break;
        }
    }
    /* exit(evaluate(engine, argv[argc-1])); */
    /* exit(evaluate(engine, ": foo cr 10 0 do 97 emit loop cr ; foo")); */

}