typedef unsigned CELL_TYPE cell;
typedef CELL_TYPE number;

typedef DOUBLE_TYPE double_number;
typedef unsigned DOUBLE_TYPE double_cell;

/*{ address_model }*/

#define c_msb ((cell)1 << (sizeof(cell) * 8 - 1))

#define _from_high_word(x) ((x) >> (sizeof(number)*8))
#define _from_low_word(x)  ((x) & (((double_number)1 << (sizeof(number)*8)) - 1))
#define _to_high_word(x)   (((double_number)(x)) << (sizeof(number)*8))
#define _to_low_word(x)    ((double_number)(x))

/* Used in when saving and loading evaluator images */
enum block_type {
    bt_data,
    bt_primitive_references,
    bt_relocation_table,
};

#define c_immediate                  0b000000001
#define c_inline1                    0b000000010
#define c_inline2                    0b000000100
#define c_inline3                    0b000000110
#define c_inline_mask                0b000000110
#define c_primitive                  0b000001000
#define c_operand_ip_absolute        0b000010000
#define c_operand_ip_offset          0b000100000
#define c_operand_indirect_ip_offset 0b001000000
#define c_operand_literal            0b010000000
#define c_operand_2literal           0b100000000

#define _quote(x) #x
#define _from_pr(x) _from_pv(_pr_value(x))

#define _string_len(x)  *(unsigned char *)(x)
#define _string_addr(x) (char *)((unsigned char *)(x) + 1)

#define _compile_pr(x) _store_data(_from_pr(x))
#define _compile_cw(x) _store_data(e[e[ea_size] / sizeof(cell) - x - 1])

#define _set_word_flags(x, flags)       *((cell *)(x) + 2) |= (flags)
#define _clear_word_flags(x, flags)     *((cell *)(x) + 2) &= ~(flags)
#define _get_word_flags(x)              *((cell *)(x) + 2)
#define _get_inline_flag(flags)         (flags & c_inline_mask)

#define _get_word_interpretation_ptr(x) ((cell *)(x) + 3)
#define _get_word_interpretation(x)     _from_ptr(_get_word_interpretation_ptr(x))

#define _store_word_name()                                        \
do {                                                              \
    register cell name = _from_ptr(dp);                           \
    register cell *string_addr = _to_ptr(*sp);                    \
    register unsigned char n = *(unsigned char *)string_addr;         \
                                                                  \
    memcpy(dp, string_addr, n + 1);             \
    dp += n + 1;                                \
                                                                  \
    *sp = name;                                                   \
                                                                  \
} while (0)

#define _word_header(flags)                                       \
       /* _word_header: ( n -- addr ) [xp]    */                  \
                                                                  \
       /* Align dp to a cell boundary.      */                    \
       dp = (char *)_align(dp);                                   \
                                                                  \
       /* Save address of new word.           */                  \
       *--rp = _from_ptr(dp);                                     \
                                                                  \
       /* Copy name address to word entry.    */                  \
       _store_data(*sp++);                                        \
                                                                  \
       /* Vocabulary list link.               */                  \
       _store_data(*_to_ptr(tp[ta_current]));                     \
                                                                  \
       /* Save word address for _end_define_word */               \
       *--sp = *rp++;                                             \
                                                                  \
       /* Word flags.                         */                  \
       _store_data(flags)

#define _next_word(x) *(_to_ptr(x) + 1)

#define _compiled_word_ref(e, l) e[e[ea_size] / sizeof(cell) - l - 1]
#define _register_compiled_word(l) _compiled_word_ref(e, l) = _from_ptr(dp)
#define _compiled_word(s, l, flags)                               \
        _begin_define_word(s, flags);                             \
        _register_compiled_word(l)

#define _begin_define_word(s, flags)                              \
    do {                                                          \
        *--sp = _from_ptr(dp);                                    \
        dp = store_counted_string((s), dp);                       \
        _word_header(flags);                                      \
    } while(0)

#define _end_define_word()                                        \
       /* Add to current vocabulary.          */                  \
       *_to_ptr(tp[ta_current]) = *sp++;

#define _define_primitive_ext(s, l, cw_l, flags)                  \
        _info("defining %-16s %lx\n", s, (long)_from_pr(l));      \
        _begin_define_word(s, c_inline1 | c_primitive | (flags)); \
        _register_compiled_word(cw_l);                            \
        _compile_pr(l);                                           \
        _compile_pr(op_exit);                                     \
        _end_define_word();

#define _compile_parse_word()                                     \
        _compile_literal(32);                                     \
        _compile_literal(_from_ptr(&e[ea_word_buffer1]));         \
        _compile_pr(pr_fetch);                                    \
        _compile_pr(pr_word)

#define _define_parsing_primitive(s, l, cw_l)                     \
        _info("defining %-16s %lx\n", s, (long)_from_pr(l));      \
        _begin_define_word(s, c_primitive);                       \
        _register_compiled_word(cw_l);                            \
        _compile_parse_word();                                    \
        _compile_pr(l);                                           \
        _compile_pr(op_exit);                                     \
        _end_define_word();

#define _define_primitive(s, l, cw_l)           _define_primitive_ext(s, l, cw_l, 0)
#define _define_immediate_primitive(s, l, cw_l) _define_primitive_ext(s, l, cw_l, c_immediate)

#define _define_constant(s, v)                                    \
        _info("defining constant %-16s %d\n", s, v);              \
        _begin_define_word(s, c_inline2);                         \
        _compile_literal(v);                                      \
        _compile_pr(op_exit);                                     \
        _end_define_word();

#define _to_buffer_ptr(n) ((char *)_to_ptr(e[ea_buffers] + n * e[ea_buffer_size]))

#define _enter()                                                  \
do {                                                              \
    *--rp = _from_ptr(ip+1);                                      \
    ip = _to_ptr(*ip);                                            \
    _check_return_stack_bounds();                                 \
} while (0)

#if VERBOSE

#define _info(...) fprintf(stderr, __VA_ARGS__)
#define _debug(...) fprintf(stderr, __VA_ARGS__)

#define _print_stack()                                                   \
do {                                                                     \
    register cell *spx = sp0;                                            \
                                                                         \
   _debug("stack: ");                                                    \
                                                                         \
    while (sp < spx)                                                     \
        _debug("%lx ", (long)*--spx);                                    \
                                                                         \
    _debug("\n");                                                        \
} while(0)

#define _print_return_stack()                                            \
do {                                                                     \
    register cell *rpx = rp0;                                            \
                                                                         \
    _debug("return stack: ");                                            \
                                                                         \
    while (rp < rpx)                                                     \
        _debug("%lx ", (long)*--rpx);                                    \
                                                                         \
    _debug("\n");                                                        \
} while(0)

#define _print_registers()                                               \
do {                                                                     \
    _debug("ip: %8lx; *ip: %8lx, *(ip+1): %8lx, rp: %8lx, *rp: %8lx, sp: %8lx, *sp: %8lx, dp: %8lx src: %.*s\n",  \
           _from_ptr(ip), ip?*ip:0, ip?*(ip+1):0,        \
           _from_ptr(rp), rp?*rp:0,                      \
           _from_ptr(sp), sp?*sp:0,                      \
           (long)_from_ptr(dp),                          \
           e[ea_source_len]-e[ea_source_idx], \
           (char *)_to_ptr(e[ea_source_addr]) + e[ea_source_idx]);      \
} while (0)

#else

#if LOG
#define _info(...) fprintf(stderr, __VA_ARGS__)
#else
#define _info(...)
#endif

#define _debug(...)
#define _print_stack()
#define _print_return_stack()
#define _print_registers()
#endif

#if TRACE

#define _trace(label)                                                    \
    do {                                                                 \
        _debug("%40s", label);                                          \
        _print_registers();                                             \
    } while(0)

#else

#define _trace(label)

#endif

#ifdef BOUNDS_CHECKING

#define _check_buffer_address(x)

#define _check_dictionary_bounds()                   \
do {                                                 \
    if (dp >= top)                                   \
        _abort(err_dictionary_overflow);             \
} while (0)

#define _check_loader_context_stack_bounds()

#define _check_minimum_stack_depth(n)                \
do {                                                 \
    if ((sp0 - sp) < (n))                            \
    _abort(err_parameter_stack_underflow);           \
} while (0)

#define _check_parameter_stack_bounds()              \
do {                                                 \
    if (sp > sp0)                                    \
        _abort(err_parameter_stack_underflow);       \
    else if (sp < sp0 - e[ea_parameter_stack_size])  \
        _abort(err_parameter_stack_overflow);        \
} while (0)

#define _check_return_stack_bounds()                 \
do {                                                 \
    if (rp > rp0)                                    \
        _abort(err_return_stack_underflow);          \
    else if (rp < rp0 - e[ea_return_stack_size])     \
        _abort(err_return_stack_overflow);           \
} while (0)

#define _is_valid_0_based_stack_index(n) ((n) >= 0 && sp + (n) < sp0)
#define _is_valid_1_based_stack_index(n) ((n) > 0 && sp + (n) <= sp0)

#else

#define _check_buffer_address()
#define _check_dictionary_bounds()
#define _check_loader_context_stack_bounds()
#define _check_minimum_stack_depth(n)
#define _check_parameter_stack_bounds()
#define _check_return_stack_bounds()

#define _is_valid_0_based_stack_index(n) 1
#define _is_valid_1_based_stack_index(n) 1

#endif

/*{ evaluator_decls }*/

extern int evaluate(cell *evaluator, const char *source, int storage_fd, cell *primitive_registry);
extern cell *create_evaluator_image(cell *e0, cell *e1, int *image_size);
extern cell *load_evaluator_image(const char *image, int image_size);

/*{ execution_model_decls }*/
/*{ primitive_decls }*/
