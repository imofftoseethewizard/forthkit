{{{extra_headers}}}

#define BUFFER_COUNT             {{{buffer_count}}}
#define BUFFER_SIZE              {{{buffer_size}}}
#define CELL_TYPE                {{{cell_type}}}
#define DOUBLE_TYPE              {{{double_type}}}
#define LENGTH_TYPE              {{{length_type}}}
#define MAX_WORD_LENGTH          {{{max_word_length}}}
#define PARAMETER_STACK_SIZE     {{{parameter_stack_size}}}
#define RETURN_STACK_SIZE        {{{return_stack_size}}}
#define SOURCE_SIZE              {{{source_size}}}

/* Diagnostic output control */
#define LOG                      {{{diagnostic.log}}}
#define TRACE                    {{{diagnostic.trace}}}
#define VERBOSE                  {{{diagnostic.verbose}}}

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

{{{memory_model}}}



int
evaluate(cell *engine, const char *source, int storage_fd)
{
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
        e[ea_here]        = e[ea_sp] + BUFFER_COUNT * sizeof(cell);

        /* internal state */
        e[ea_base]        = 10;
        e[ea_context]     = 0;
        e[ea_current]     = _from_ptr(&e[ea_forth]);
        e[ea_data]        = e[ea_here];
        e[ea_forth]       = 0;
        e[ea_rp0]         = e[ea_rp];
        e[ea_source_idx]  = 0;
        e[ea_source_len]  = 0;
        e[ea_sp0]         = e[ea_sp];
        e[ea_state]       = 0;
        e[ea_interpret]   = 0;
        e[ea_source_addr] = _from_ptr(&e[engine_attribute_count]);
        e[ea_blk]         = 0;
        e[ea_buffers]     = e[ea_sp];
        e[ea_next_buffer] = 0;
        e[ea_scr]         = 0;

        for (register int i = 0; i < BUFFER_COUNT; i++)
            e[e[ea_buffers] + i] = -1;
    }

    /* These are generally useful to have, but probably not worth putting
       in a register.
     */
    char *here = (char *)_to_ptr(e[ea_here]);
    cell *rp0  = (cell *)_to_ptr(e[ea_rp0]);
    cell *sp0  = (cell *)_to_ptr(e[ea_sp0]);

    /* Contains the throw code for uncaught exceptions. */
    int result = 0;

    /* The threading module must be included before any operators or
       primitives.
     */
    #include "../threading/direct.c"
    /* #include "../threading/subroutine.c" */
    /* #include "../threading/switch.c" */

    #include "../primitive/op/abort.c"
    #include "../primitive/op/branch.c"
    #include "../primitive/op/do.c"
    #include "../primitive/op/does.c"
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
    #include "../primitive/core/zero_lt.c"

    #include "../primitive/core/compile_begin.c"
    #include "../primitive/core/compile_else.c"
    #include "../primitive/core/compile_if.c"
    #include "../primitive/core/compile_then.c"
    #include "../primitive/core/compile_repeat.c"
    #include "../primitive/core/compile_until.c"
    #include "../primitive/core/compile_while.c"

    #include "../bootstrap/interpret-79.c"
    /* End of bootstrap */

    #include "../primitive/core/posix/emit.c"
    #include "../primitive/core/posix/key.c"
    #include "../primitive/core/posix/readline/expect.c"

    #include "../primitive/core/abort.c"
    #include "../primitive/core/abs.c"
    #include "../primitive/core/allot.c"
    #include "../primitive/core/base.c"
    #include "../primitive/core/c_comma.c"
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
    #include "../primitive/core/convert.c"
    #include "../primitive/core/cr.c"
    #include "../primitive/core/current.c"
    #include "../primitive/core/dash_trailing.c"
    #include "../primitive/core/decimal.c"
    #include "../primitive/core/definitions.c"
    #include "../primitive/core/depth.c"
    #include "../primitive/core/div.c"
    #include "../primitive/core/div_mod.c"
    #include "../primitive/core/does.c"
    #include "../primitive/core/dot_quote.c"
    #include "../primitive/core/d_lt.c"
    #include "../primitive/core/d_negate.c"
    #include "../primitive/core/d_plus.c"
    #include "../primitive/core/eq.c"
    #include "../primitive/core/exit.c"
    #include "../primitive/core/fill.c"
    #include "../primitive/core/forth.c"
    #include "../primitive/core/gt.c"
    #include "../primitive/core/here.c"
    #include "../primitive/core/hold.c"
    #include "../primitive/core/i.c"
    #include "../primitive/core/immediate.c"
    #include "../primitive/core/j.c"
    #include "../primitive/core/leave.c"
    #include "../primitive/core/left_bracket.c"
    #include "../primitive/core/lshift.c"
    #include "../primitive/core/lt.c"
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
    #include "../primitive/core/paren.c"
    #include "../primitive/core/plus.c"
    #include "../primitive/core/plus_store.c"
    #include "../primitive/core/posix/type.c"
    #include "../primitive/core/quit.c"
    #include "../primitive/core/r_fetch.c"
    #include "../primitive/core/r_from.c"
    #include "../primitive/core/right_bracket.c"
    #include "../primitive/core/rot.c"
    #include "../primitive/core/rshift.c"
    #include "../primitive/core/semicolon.c"
    #include "../primitive/core/sign.c"
    #include "../primitive/core/store.c"
    #include "../primitive/core/times.c"
    #include "../primitive/core/times_div.c"
    #include "../primitive/core/times_div_mod.c"
    #include "../primitive/core/to_in.c"
    #include "../primitive/core/to_r.c"
    #include "../primitive/core/two_minus.c"
    #include "../primitive/core/two_plus.c"
    #include "../primitive/core/u_lt.c"
    #include "../primitive/core/u_div_mod.c"
    #include "../primitive/core/u_times.c"
    #include "../primitive/core/variable.c"
    #include "../primitive/core/xor.c"
    #include "../primitive/core_ext/pick.c"
    #include "../primitive/core_ext/roll.c"

    #include "../primitive/block/blk.c"
    #include "../primitive/block/block.c"
    #include "../primitive/block/buffer.c"
    #include "../primitive/block/empty-buffers.c"
    #include "../primitive/block/list.c"
    #include "../primitive/block/load.c"
    #include "../primitive/block/save-buffers.c"
    #include "../primitive/block/scr.c"
    #include "../primitive/block/update.c"

    #include "../primitive/core/posix/dot.c"
    #include "../primitive/core/posix/u_dot.c"

    #include "../compiled/core/79_standard.c"
    #include "../compiled/core/bracket_compile.c"
    #include "../compiled/core/num_s.c"
    #include "../compiled/core/query.c"
    #include "../compiled/core/question_mark.c"
    #include "../compiled/core/space.c"
    #include "../compiled/core/spaces.c"
    #include "../compiled/core/tick_f79.c"
    #include "../compiled/core/word.c"
    #include "../compiled/core/forget.c"

    /* The first run will have context == 0. The preamble detects that and
       defines primitives and the bootstrap interpreter.
     */
    if (!e[ea_context])
        e[ea_context] = _from_ptr(&e[ea_forth]);

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
