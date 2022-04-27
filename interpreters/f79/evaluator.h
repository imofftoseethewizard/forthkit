#include "engine/config.h"
#include "engine/log.h"

typedef unsigned CELL_TYPE cell;
typedef CELL_TYPE number;

#define c_msb ((cell)1 << (sizeof(cell) * 8 - 1))

typedef LENGTH_TYPE length_type;

typedef DOUBLE_TYPE double_number;
typedef unsigned DOUBLE_TYPE double_cell;

#define _from_high_word(x) ((x) >> (sizeof(number)*8))
#define _from_low_word(x)  ((number)(x))
#define _to_high_word(x)   (((double_number)(x)) << (sizeof(number)*8))
#define _to_low_word(x)    ((double_number)(x))

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
    ea_forth,
    ea_rp0,
    ea_source_idx,
    ea_source_len,
    ea_sp0,
    ea_state,
    ea_interpret,
    ea_source_addr,
    ea_blk,
    ea_buffers,
    ea_next_buffer,
    ea_scr,

    /* must be last */
    engine_attribute_count
};

#define c_immediate 0b0001
#define c_inline    0b0010
#define c_primitive 0b0100
#define c_value     0b1000

#define _quote(x) #x
#define _from_pr(x) _from_pv(_pr_value(x))
#define _register_operator(x, y)                                           \
    do {                                                                   \
        if (!e[ea_context])                                                \
            _debug("operator %-16s %lx\n", _quote(y), (long)_from_pr(y));  \
    } while (0)

#define _string_len(x)  *(length_type *)(x)
#define _string_addr(x) (char *)((length_type *)(x) + 1)

#define _compile_pr(x) _store_data(_from_pr(x))
#define _compile_cw(x) _store_data(e[ea_size - x - 1])

#define _set_word_flags(x, flags)       *((cell *)(x) + 2) |= (flags)
#define _clear_word_flags(x, flags)     *((cell *)(x) + 2) &= ~(flags)
#define _get_word_flags(x, flags)       *((cell *)(x) + 2) & ~(flags)

#define _get_word_interpretation_ptr(x) ((cell *)(x) + 3)
#define _get_word_interpretation(x)     _from_ptr(_get_word_interpretation_ptr(x))

#define _store_word_name()                                                 \
do {                                                                       \
    register cell name = _from_ptr(here);                                  \
    register cell *string_addr = _to_ptr(*sp);                             \
    register length_type n = *(length_type *)string_addr;                  \
                                                                           \
    memcpy(here, string_addr, n + sizeof(length_type));                    \
    here += n + sizeof(length_type);                                       \
                                                                           \
    *sp = name;                                                            \
                                                                           \
} while (0)


#define _word_header(flags)                                                \
       /* _word_header: ( n -- addr ) [xp]    */                           \
                                                                           \
       /* Align here to a cell boundary.      */                           \
       here = (char *)_align(here);                                        \
                                                                           \
       /* Save address of new word.           */                           \
       *--rp = _from_ptr(here);                                            \
                                                                           \
       /* Copy name address to word entry.    */                           \
       _store_data(*sp++);                                                 \
                                                                           \
       /* Vocabulary list link.               */                           \
       _store_data(*_to_ptr(e[ea_current]));                               \
                                                                           \
       /* Add to current vocabulary.          */                           \
       *_to_ptr(e[ea_current]) = *rp++;                                    \
                                                                           \
       /* Word flags.                         */                           \
       _store_data(flags)

#define _next_word(x) *(_to_ptr(x) + 1)

#define _compiled_word_ref(e, l) e[e[ea_size] / sizeof(cell) - l - 1]
#define _register_compiled_word(l) _compiled_word_ref(e, l) = _from_ptr(here);
#define _compiled_word(s, l, flags) \
        _begin_define_word(s, flags); \
        _register_compiled_word(l)

#define _begin_define_word(s, flags)                                       \
    do {                                                                   \
        *--sp = _from_ptr(here);                                           \
        here = store_counted_string((s), here);                            \
        _word_header(flags);                                               \
    } while(0)

#define _define_primitive_ext(s, l, cw_l, flags)                                 \
        _info("defining %-16s %lx\n", s, (long)_from_pr(l));               \
        _begin_define_word(s, c_inline | c_primitive | (flags));           \
        _register_compiled_word(cw_l);                           \
        _compile_pr(l);                                                    \
        _compile_pr(op_exit);

#define _define_parsing_primitive(s, l, cw_l)                                    \
        _info("defining %-16s %lx\n", s, (long)_from_pr(l));               \
        _begin_define_word(s, c_primitive);                                \
        _register_compiled_word(cw_l);                           \
        _compile_literal(MAX_WORD_LENGTH);                                 \
        _compile_pr(pr_allot);                                             \
        _compile_literal(32);                                              \
        _compile_pr(pr_word);                                              \
        _compile_literal(-MAX_WORD_LENGTH);                                \
        _compile_pr(pr_allot);                                             \
        _compile_pr(l);                                                    \
        _compile_pr(op_exit);

#define _define_primitive(s, l, cw_l)           _define_primitive_ext(s, l, cw_l, 0)
#define _define_immediate_primitive(s, l, cw_l) _define_primitive_ext(s, l, cw_l, c_immediate)

#define _to_ptr(x)   (cell *)((char *)e + (x))
#define _from_ptr(x) (cell)((char *)(x) - (char *)e)

#define c_primitive_flag (1L << (sizeof(cell) * 8 - 1))

#define _is_primitive(x)  (((long)(x)) & c_primitive_flag)
#define _from_pv(x) (void *)((x) - _pr_value_base | c_primitive_flag)
#define _to_pv(x) (((x) & ~ c_primitive_flag) + _pr_value_base)
__include_primitive(primitive / op / abort.m4)
    __include_primitive(primitive / op / branch.m4)
    __include_primitive(primitive / op /
			do
			.m4)
	__include_primitive(primitive / op / does.m4)
	__include_primitive(primitive / op / exit.m4)
	__include_primitive(primitive / op / jump.m4)
	__include_primitive(primitive / op / literal.m4)
	__include_primitive(primitive / op / loop.m4)
	__include_primitive(primitive / op / plus_loop.m4)
	__include_primitive(primitive / block / blk.m4)
	__include_primitive(primitive / block / block.m4)
	__include_primitive(primitive / block / buffer.m4)
	__include_primitive(primitive / block / empty - buffers.m4)
	__include_primitive(primitive / block / save - buffers.m4)
	__include_primitive(primitive / block / scr.m4)
	__include_primitive(primitive / block / update.m4)
	__include_primitive(primitive / core / abort.m4)
	__include_primitive(primitive / core / abs.m4)
	__include_primitive(primitive / core / align.m4)
	__include_primitive(primitive / core / allot.m4)
	__include_primitive(primitive / core / and.m4)
	__include_primitive(primitive / core / base.m4)
	__include_primitive(primitive / core / c_comma.m4)
	__include_primitive(primitive / core / c_fetch.m4)
	__include_primitive(primitive / core / c_move.m4)
	__include_primitive(primitive / core / c_store.m4)
	__include_primitive(primitive / core / colon.m4)
	__include_primitive(primitive / core / compile.m4)
	__include_primitive(primitive / core / compile_begin.m4)
	__include_primitive(primitive / core / compile_do.m4)
	__include_primitive(primitive / core / compile_else.m4)
	__include_primitive(primitive / core / compile_if.m4)
	__include_primitive(primitive / core / compile_loop.m4)
	__include_primitive(primitive / core / compile_plus_loop.m4)
	__include_primitive(primitive / core / compile_repeat.m4)
	__include_primitive(primitive / core / compile_then.m4)
	__include_primitive(primitive / core / compile_until.m4)
	__include_primitive(primitive / core / compile_while.m4)
	__include_primitive(primitive / core / constant.m4)
	__include_primitive(primitive / core / context.m4)
	__include_primitive(primitive / core / convert.m4)
	__include_primitive(primitive / core / count.m4)
	__include_primitive(primitive / core / cr.m4)
	__include_primitive(primitive / core / create.m4)
	__include_primitive(primitive / core / current.m4)
	__include_primitive(primitive / core / d_lt.m4)
	__include_primitive(primitive / core / d_negate.m4)
	__include_primitive(primitive / core / d_plus.m4)
	__include_primitive(primitive / core / dash_trailing.m4)
	__include_primitive(primitive / core / decimal.m4)
	__include_primitive(primitive / core / definitions.m4)
	__include_primitive(primitive / core / depth.m4)
	__include_primitive(primitive / core / div.m4)
	__include_primitive(primitive / core / div_mod.m4)
	__include_primitive(primitive / core / does.m4)
	__include_primitive(primitive / core / dot.m4)
	__include_primitive(primitive / core / dot_quote.m4)
	__include_primitive(primitive / core / drop.m4)
	__include_primitive(primitive / core / dup.m4)
	__include_primitive(primitive / core / emit.m4)
	__include_primitive(primitive / core / eq.m4)
	__include_primitive(primitive / core / execute.m4)
	__include_primitive(primitive / core / fetch.m4)
	__include_primitive(primitive / core / fill.m4)
	__include_primitive(primitive / core / find - 79. m4)
	__include_primitive(primitive / core / forth.m4)
	__include_primitive(primitive / core / gt.m4)
	__include_primitive(primitive / core / here.m4)
	__include_primitive(primitive / core / hold.m4)
	__include_primitive(primitive / core / i.m4)
	__include_primitive(primitive / core / immediate.m4)
	__include_primitive(primitive / core / j.m4)
	__include_primitive(primitive / core / key.m4)
	__include_primitive(primitive / core / leave.m4)
	__include_primitive(primitive / core / left_bracket.m4)
	__include_primitive(primitive / core / literal.m4)
	__include_primitive(primitive / core / lshift.m4)
	__include_primitive(primitive / core / lt.m4)
	__include_primitive(primitive / core / max.m4)
	__include_primitive(primitive / core / min.m4)
	__include_primitive(primitive / core / minus.m4)
	__include_primitive(primitive / core / mod.m4)
	__include_primitive(primitive / core / move.m4)
	__include_primitive(primitive / core / negate.m4)
	__include_primitive(primitive / core / not.m4)
	__include_primitive(primitive / core / num.m4)
	__include_primitive(primitive / core / num_end.m4)
	__include_primitive(primitive / core / num_start.m4)
	__include_primitive(primitive / core / one_minus.m4)
	__include_primitive(primitive / core / one_plus.m4)
	__include_primitive(primitive / core / or.m4)
	__include_primitive(primitive / core / over.m4)
	__include_primitive(primitive / core / paren.m4)
	__include_primitive(primitive / core / plus.m4)
	__include_primitive(primitive / core / plus_store.m4)
	__include_primitive(primitive / core / posix / readline / expect.m4)
	__include_primitive(primitive / core / q_dup.m4)
	__include_primitive(primitive / core / quit.m4)
	__include_primitive(primitive / core / r_fetch.m4)
	__include_primitive(primitive / core / r_from.m4)
	__include_primitive(primitive / core / right_bracket.m4)
	__include_primitive(primitive / core / rot.m4)
	__include_primitive(primitive / core / rshift.m4)
	__include_primitive(primitive / core / semicolon.m4)
	__include_primitive(primitive / core / sign.m4)
	__include_primitive(primitive / core / state.m4)
	__include_primitive(primitive / core / store.m4)
	__include_primitive(primitive / core / store_compiled.m4)
	__include_primitive(primitive / core / store_data.m4)
	__include_primitive(primitive / core / swap.m4)
	__include_primitive(primitive / core / times.m4)
	__include_primitive(primitive / core / times_div.m4)
	__include_primitive(primitive / core / times_div_mod.m4)
	__include_primitive(primitive / core / to_in.m4)
	__include_primitive(primitive / core / to_number.m4)
	__include_primitive(primitive / core / to_r.m4)
	__include_primitive(primitive / core / two_minus.m4)
	__include_primitive(primitive / core / two_plus.m4)
	__include_primitive(primitive / core / type.m4)
	__include_primitive(primitive / core / u_div_mod.m4)
	__include_primitive(primitive / core / u_dot.m4)
	__include_primitive(primitive / core / u_lt.m4)
	__include_primitive(primitive / core / u_times.m4)
	__include_primitive(primitive / core / variable.m4)
	__include_primitive(primitive / core / word.m4)
	__include_primitive(primitive / core / xor.m4)
	__include_primitive(primitive / core / zero_eq.m4)
	__include_primitive(primitive / core / zero_gt.m4)
	__include_primitive(primitive / core / zero_lt.m4)
	__include_primitive(primitive / core_ext / pick.m4)
	__include_primitive(primitive / core_ext / roll.m4)
	__include_compiled_word(compiled / core / num_s.m4)
	__include_compiled_word(compiled / core / 79 _standard.m4)
	__include_compiled_word(compiled / core / word.m4)
	__include_compiled_word(compiled / core / forget.m4)
	__include_compiled_word(compiled / core / tick_f79.m4)
	__include_compiled_word(compiled / core / bracket_compile.m4)
	__include_compiled_word(compiled / core / question_mark.m4)
	__include_compiled_word(compiled / core / spaces.m4)
	__include_compiled_word(compiled / core / space.m4)
	__include_compiled_word(compiled / core / query.m4)
	__include_compiled_word(compiled / block / block.m4)
	__include_compiled_word(compiled / block / load.m4)
	__include_compiled_word(compiled / block / list.m4)
	__include_compiled_word(compiled / bootstrap / f79 - interpret.m4)
enum compiled_word_labels {
};

__discard_all_diversions()
