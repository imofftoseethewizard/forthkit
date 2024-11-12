/*{ title_block }*/

/*{ generation_details }*/

	#include <errno.h>
	#include <fcntl.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <readline/readline.h>
	#include <unistd.h>

	#include "evaluator.h"

/*|

The address model is either host or virtual.  (See the
templates/address_model directory.)  The host address model uses the
address space of the process running the evaluator.  The virtual
address model has a 0-based virtual address space.  There must be
agreement between the compilation target and the host address model in
that a pointer must fit into one cell.

The address model defines several macros which allow the translation
of cell references to host addresses, and from cell representations of
primitives to the value associated with the primitive's label
generated by the compiler.

`_to_ptr(x)` takes a cell-valued reference to another cell and returns
a pointer to the memory containing that cell.  No check is made that
the cell reference is actually within the evaluator's address space.

`_from_ptr(x)` takes a pointer to a memory address and returns the
cell value which refers to the cell that occupies that memory address.
No check is made that the pointer references memory within the
evaluator's address space.

In direct threaded evaluators, references to primitives may appear
throughout the definition of a word and we require a way to
distinguish them from defined words.  `_is_primitive(x)` accepts a
cell value and returns true if is refers to a primitive.  In indirect
threaded evaluators, references to primitives only appear in the cfa
of words, and the `_is_primitive` macro is not necessary and is
therefore not defined.

A _primitive value_ is the value the compiler assigns to the
primitive's label.  Depending on the execution model, it may be the
address of a subroutine, the address of a label for use with goto, or
an enumerated value used in a case statement.  The `_from_pv(x)` macro
accepts a primitive value and returns a cell value which represents
it.  `_to_pv(x)` provides the inverse functionality, accepting a cell
value and returning the primitive value it represents.  Note that no
check is made in either case for the validity of either the cell
representation nor that the primitive value is valid.

All of the macros above should only be expanded in the evaluator's
lexical context.  There are three symbols which appear in `host.h` and
`virtual.h` from that context. `e` is a `cell[]` value referring to
the address space of the evaluator. `_pr_value_base` and
`_pr_value_limit` are the numerical lower and upper limits of
primitive values.  In some configurations, none of these are
referenced -- indirect threaded host addressing, for example.
Nonetheless, it would be difficult to expand these successfully
outside of that context in a way that is unaware of the address or
execution model.

  |*/

/*{ address_model }*/

/*{ execution_model_decls }*/

    #define _from_pr(x) _from_pv(_pr_value(x))

/*|

`c_msb` is a cell value with a 1 in the most significant bit and
zeroes elsewhere.

  |*/

    #define c_msb ((cell)1 << (sizeof(cell) * 8 - 1))

/*|

These are some utility macros used to pack and unpack double numbers,
primarily used in the implementation of primitives.

`_from_high_word` accepts a `double number` and returns a `double
number` containing the upper half of the `double number` in its lower
half, the upper half being 0.

`_from_low_word` is similar, but the source is the low word.

The result of these two functions can be safely cast to a `number`.

The other two macros accept a `number` and return a `double number`,
performing the reverse operation to those above.

  |*/

	#define _from_high_word(x) ((x) >> (sizeof(number)*8))
	#define _from_low_word(x)  ((x) & (((double_number)1 << (sizeof(number)*8)) - 1))
	#define _to_high_word(x)   (((double_number)(x)) << (sizeof(number)*8))
	#define _to_low_word(x)    ((double_number)(x))

/*|

Built-in string handling for use with storing and retrieving the names
of words uses a length-prefixed format.  Given the limited intended
use, the length is just a single byte and refers the the length of
data stored, not the number of characters.

`_string_len` accepts the address of a string and returns its length.

`_string_addr` accepts the address of a string and returns the address
of the contents of the string.

  |*/

    #define _string_len(x)  *(unsigned char *)(x)
    #define _string_addr(x) (char *)((unsigned char *)(x) + 1)

/*|

TODO

  |*/

#define _compile_pr(x) _store_data(_from_pr(x))
#define _compile_cw(x) _store_data(e[e[ea_size] / sizeof(cell) - x - 1])

/*|

In an earlier version of Forthkit, there were numerous flags that
could be set on a word.  Over the evolution of the project all but
`c_immediate` became disused and were removed.

  |*/

#define c_immediate 0b1

#define _set_word_flags(x, flags)       *((cell *)(x) + 2) |= (flags)
#define _clear_word_flags(x, flags)     *((cell *)(x) + 2) &= ~(flags)
#define _get_word_flags(x)              *((cell *)(x) + 2)

/*|

TODO

  |*/

#define _get_word_interpretation_ptr(x) ((cell *)(x) + 3)
#define _get_word_interpretation(x)     _from_ptr(_get_word_interpretation_ptr(x))

/*|

TODO

  |*/

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

/*|

TODO

  |*/

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

/*|

TODO

  |*/

#define _next_word(x) *(_to_ptr(x) + 1)

/*|

TODO

  |*/

#define _compiled_word_ref(e, l) e[e[ea_size] / sizeof(cell) - l - 1]
#define _register_compiled_word(l) _compiled_word_ref(e, l) = _from_ptr(dp)
#define _compiled_word(s, l, flags)                               \
        _begin_define_word(s, flags);                             \
        _register_compiled_word(l)

/*|

TODO

  |*/

#define _begin_define_word(s, flags)                              \
    do {                                                          \
        *--sp = _from_ptr(dp);                                    \
        dp = store_counted_string((s), dp);                       \
        _word_header(flags);                                      \
    } while(0)

/*|

TODO

  |*/

#define _end_define_word()                                        \
       /* Add to current vocabulary.          */                  \
       *_to_ptr(tp[ta_current]) = *sp++;

/*|

TODO

  |*/

#define _define_primitive_ext(s, l, cw_l, flags)                  \
        _info("defining %-16s %lx\n", s, (long)_from_pr(l));      \
        _begin_define_word(s, (flags));                           \
        _register_compiled_word(cw_l);                            \
        _compile_pr(l);                                           \
        _compile_pr(op_exit);                                     \
        _end_define_word();

/*|

TODO

  |*/

#define _compile_parse_word()                                     \
        _compile_literal(32);                                     \
        _compile_literal(_from_ptr(&e[ea_word_buffer1]));         \
        _compile_pr(pr_fetch);                                    \
        _compile_pr(pr_word)

/*|

TODO

  |*/

#define _define_parsing_primitive(s, l, cw_l)                     \
        _info("defining %-16s %lx\n", s, (long)_from_pr(l));      \
        _begin_define_word(s, 0);                                 \
        _register_compiled_word(cw_l);                            \
        _compile_parse_word();                                    \
        _compile_pr(l);                                           \
        _compile_pr(op_exit);                                     \
        _end_define_word();

/*|

TODO

  |*/

#define _define_primitive(s, l, cw_l)           _define_primitive_ext(s, l, cw_l, 0)
#define _define_immediate_primitive(s, l, cw_l) _define_primitive_ext(s, l, cw_l, c_immediate)

/*|

TODO

  |*/

#define _define_constant(s, v)                                    \
        _info("defining constant %-16s %d\n", s, v);              \
        _begin_define_word(s, 0);                                 \
        _compile_literal(v);                                      \
        _compile_pr(op_exit);                                     \
        _end_define_word();

/*|

TODO

  |*/

#define _to_buffer_ptr(n) ((char *)_to_ptr(e[ea_buffers] + n * e[ea_buffer_size]))

/*|

TODO

  |*/

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

/*{ additional_definitions }*/
char *store_counted_string(const char *s, char *dp);

/*{ evaluator_impl }*/

int
evaluate_source(cell *evaluator, const char *source, int storage_fd)
{
	return evaluate(evaluator, source, storage_fd, NULL);
}

char *
store_counted_string(const char *s, char *dp)
{
    cell n = strlen(s);

    dp = (char *)_align(dp);

    *(unsigned char *)dp = n;

    strncpy((char *)((unsigned char *)dp + 1), s, n);

    return dp + sizeof(cell) + n + 1;
}

int
image_block_size(int payload_size)
{
    return payload_size + 3 * sizeof(cell);
}

/* Used in when saving and loading evaluator images */
enum block_type {
    bt_data,
    bt_primitive_references,
    bt_relocation_table,
};

cell *
add_image_block(cell *image, int image_size, cell block_type, cell length, cell offset, char *data, int *image_size_out)
{
    int block_size = image_block_size(length);
    int new_image_size = image_size + block_size;
    cell *imp;

    image = realloc(image, new_image_size);
    imp = (cell *)((char *)image + image_size);

    *imp++ = block_type;
    *imp++ = length;
    *imp++ = offset;

    memcpy((char *)imp, data, length);

    *image_size_out = new_image_size;
    return image;
}

cell *
add_primitive_table_block(
    cell *image, int image_size, cell length, char *data, int *image_size_out)
{
    return add_image_block(image, image_size, bt_primitive_references, length,
                           0, data, image_size_out);
}

cell *
add_relocation_table_block(
    cell *image, int image_size, cell length, char *data, int *image_size_out)
{
    return add_image_block(
        image, image_size, bt_relocation_table, length, 0, data,
        image_size_out);
}

cell *
add_data_block(
    cell *image, int image_size, cell length, cell offset, char *data,
    int *image_size_out)
{
    return add_image_block(
        image, image_size, bt_data, length, offset, data, image_size_out);
}

cell *
create_data_image(cell *e, int *image_size)
{
    cell *image = malloc(sizeof(cell));
    char *data;

    if (!image)
        return NULL;

    *image = e[ea_size];
    *image_size = sizeof(cell);

    /* save task attributes */
    data = (char *)_to_ptr(e[ea_tasks]);
    image = add_data_block(
        image, *image_size, _task_area, (cell)(data - (char *)e), data, image_size);

    /* save fiber attributes */
    data = (char *)_to_ptr(e[ea_fibers]);
    image = add_data_block(
        image, *image_size, _fiber_area, (cell)(data - (char *)e), data, image_size);

    /* save task dictionaries (and engine attributes with task 0) */
    for (register int i = 0; i < e[ea_task_count]; i++) {
	register cell *t = _to_task_ptr(i), length = _align(t[ta_dp] - t[ta_bottom]);
        char *data = (char *)_to_ptr(t[ta_bottom]);

        if (length == 0)
            continue;

        image = add_data_block(
            image, *image_size, length, (cell)(data - (char *)e), data, image_size);
    }

    return realloc(image, *image_size);
}

cell *
create_relocation_table(cell *e0, cell *e1, cell *im0, cell *im1, int image_size, int *rt_size_out)
{
    /* relocation table */
    cell *rt = malloc(image_size), *rtp = rt;

    *rt_size_out = 0;

    if (!rt)
        return NULL;

    /* If the evaluators use relocatable addressing, then they should be
     * identical. If the use absolute addressing, then they will differ
     * at all places where there is an address, and that difference will be
     * be the same for every address and also equal to the difference between
     * the memory blocks of the two evaluators.
     */
    int offset = (char *)e1 - (char *)e0;

    for (int idx = 1; idx < image_size / sizeof(cell); idx++)
        /* Check the cell to see if contains an absolute address.
         */
        if (im1[idx] - im0[idx] == offset) {
            /* If so, compute the relative address, and store that,
             * recording the index where the relocation happened.
             */
            im0[idx] -= (cell)e0;
            *rtp++ = idx;
        }

    *rt_size_out = (char *)rtp - (char *)rt;
    return rt;
}

cell *
create_primitives_table(cell *image, int image_size, cell *rt, int rt_size, int *pt_size_out)
{
    /* The primitives table will need at most the size of the data
     * portion less any relocations. In practice it will be a lot less.
     */

    cell
      *pt = malloc(image_size - rt_size),
      *ptp = pt;

    /* Get the evaluator's list of primitives. */

    cell *primitives = malloc(/*{ primitive_count }*/ * sizeof(cell));
    evaluate(NULL, NULL, 0, primitives);

    /* Check the data blocks for primitives, using a linear search of the
     * primitives at each location, skipping relocated cells (because
     * those are definitely not primitives).
     *
     * These two items should prevent subtle errors from happening where
     * a bit of non-code data matches a primitive value. Currently not
     * necessary, and unlikely to be a problem, but should be done before
     * declaring "v1".
     *
     * TODO:
     *   1. Only process the data portions of the data blocks in the
     *      image.
     *   2. Only process the dictionary portions of the data.
     */

    for (int idx = 1, ridx = 0; idx < image_size / sizeof(cell); idx++) {

        /* Check to see if the cell at this location has been relocated.
         * If so, it's not a primitive.
         */
        if (ridx < rt_size && idx == rt[ridx])
            /* Advance to the next relocated cell. */
            ridx++;

        else
            for (int i = 0; i < /*{ primitive_count }*/; i++)

                /* Check to see if the cell at this location is a primitive.
                 */
                if (image[idx] == primitives[i]) {
                    /* Save the index and update the cell with the primitive's
                     * id.
                     */
                    *ptp++ = idx;
                    image[idx] = i;
                    break;
                }
    }

    free(primitives);

    *pt_size_out = (char *)ptp - (char *)pt;
    return pt;
}

cell *
create_evaluator_image(cell *e0, cell *e1, int *image_size)
{
    int image_size0, image_size1, rt_size, pt_size;
    cell *image, *im0, *im1, *rt, *pt;

    image = NULL;
    *image_size = 0;

    im0 = create_data_image(e0, &image_size0);
    im1 = create_data_image(e1, &image_size1);

    rt = create_relocation_table(e0, e1, im0, im1, image_size0, &rt_size);
    pt = create_primitives_table(im0, image_size0, rt, rt_size, &pt_size);

    image = im0;
    *image_size = image_size0;

    image = add_relocation_table_block(image, *image_size, rt_size, (char *)rt, image_size);
    image = add_primitive_table_block(image, *image_size, pt_size, (char *)pt, image_size);

    free(pt);
    free(rt);
    free(im1);

    return image;
}

int
next_block(char *blks, int idx, int size, cell *block_type_out, cell *length_out, cell *offset_out)
{
    cell block_type, length, offset;

    if (idx + 3 * sizeof(cell) >= size) {
        fprintf(stderr, "image format error 1\n");
        exit(2);
    }

    block_type = *(cell *)(blks + idx);
    idx += sizeof(cell);

    length = *(cell *)(blks + idx);
    idx += sizeof(cell);

    offset = *(cell *)(blks + idx);
    idx += sizeof(cell);

    if (idx + length > size) {
        fprintf(stderr, "image format error 2\n");
        exit(2);
    }

    *block_type_out = block_type;
    *length_out = length;
    *offset_out = offset;

    return idx;
}

cell *
load_evaluator_image(const char *image0, int image_size)
{
    char *image = malloc(image_size);
    cell size = *(cell *)image0;
    cell *e = (cell *)malloc(size);
    int idx = sizeof(cell);
    cell block_type, length, offset;

    memcpy(image, image0, image_size);

    cell *primitives;
    int primitive_count = evaluate(NULL, NULL, 0, &primitives);

    while (idx < image_size) {

        idx = next_block(image, idx, image_size, &block_type, &length, &offset);

        cell *prp, *rtp;

        switch (block_type) {
        case bt_primitive_references:

            prp = (cell *)(image + idx);

            for (int pidx = 0; pidx < length/sizeof(cell); pidx++, prp++)
                ((cell *)image)[*prp] = primitives[((cell *)image)[*prp]];

            break;

        case bt_relocation_table:

            rtp = (cell *)(image + idx);

            /* Does the interpreter use absolute addressing? */
            /* TODO: evaluator build attributes */
            if (sizeof(cell *) == sizeof(cell) && _from_ptr(e) == (cell)e)
                for (int ridx = 0; ridx < length/sizeof(cell); ridx++, rtp++)
                    ((cell *)image)[*rtp] += (cell)e;

            break;
        }

        idx += length;
    }

    idx = sizeof(cell);
    while (idx < image_size) {

        idx = next_block(image, idx, image_size, &block_type, &length, &offset);

        if (block_type == bt_data)
            memcpy((char *)e + offset, image + idx, length);

        idx += length;
    }

    free(image);

    return e;
}

typedef struct {
    number code;
    const char *symbol;
    const char *message;
} error_descriptor;

static const error_descriptor error_descriptors[] = {
/*{ error_descriptors }*/
};

const char *
error_message(number code)
{
    for (int i = 0; i < sizeof(error_descriptors)/sizeof(error_descriptor); i++)
        if (error_descriptors[i].code == code)
            return error_descriptors[i].message;

    return NULL;
}

int
error_code(const char *symbol)
{
    for (int i = 0; i < sizeof(error_descriptors)/sizeof(error_descriptor); i++)
        if (!strcmp(error_descriptors[i].symbol, symbol))
            return error_descriptors[i].code;

    return 0;
}
