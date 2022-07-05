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

    evaluate(e, "", -1, NULL);
}

int
evaluate(cell *evaluator, const char *source, int storage_fd, cell *primitives)
{
    __declare_evaluator_variables()

    __declare_primitives()dnl

    static cell internal_primitives[__primitive_count];

    if (!evaluator) {
        __initialize_internal_primitive_registry()dnl

        if (primitives)
            memcpy(primitives, &internal_primitives, sizeof(internal_primitives));

        return sizeof(internal_primitives)/sizeof(cell);
    }

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
image_block_size(int payload_size)
{
    return payload_size + 3 * sizeof(cell);
}

cell *
add_image_block(cell *image, int image_size, cell block_type, cell length, cell offset, char *data, int *image_size_out)
{
    int block_size = image_block_size(length);
    int new_image_size = image_size + block_size;
    cell *imp;

    image = realloc(image, new_image_size);
    imp = (char *)image + image_size;

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

    char *image = malloc(e[ea_size]);
    char *data;

    if (!image)
        return NULL;

    *(cell *)image = e[ea_size];
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
create_evaluator_image(cell *e0, cell *e1, int *image_size)
{
    int image_size0, image_size1;
    cell *im0, *im1;

    *image_size = 0;

    im0 = create_data_image(e0, &image_size0);
    im1 = create_data_image(e1, &image_size1);

    if (!im0 || !im1)
        return NULL;

    /* relocation table */
    cell *rt = malloc(image_size0), *rtp = rt;

    if (!rt)
        return NULL;

    *image_size = image_size0;

    int offset = (char *)e1 - (char *)e0;

    for (int idx = 0; idx < image_size0 / sizeof(cell); idx++)
        if (im1[idx] - im0[idx] == offset) {
            im0[idx] -= (cell)e0;
            *rtp++ = idx;
        }

    free(im1);

    int rt_size = (char *)rtp - (char *)rt;

    im0 = add_relocation_table_block(im0, *image_size, rt_size, (char *)rt, image_size);

    int primitive_count = evaluate(NULL, NULL, 0, NULL);
    cell *primitives = malloc(primitive_count * sizeof(cell));
    evaluate(NULL, NULL, 0, primitives);

    cell *pt = malloc(image_size0), *ptp = pt;

    rtp = rt;
    for (int idx = 0; idx < image_size0 / sizeof(cell); idx++) {
        for (int i = 0; i < primitive_count; i++) {
            if (idx == *rtp) {
                rtp++;
                i = primitive_count;
                break;
            }
            if (im0[idx] == primitives[i]) {
                *ptp++ = idx;
                im0[idx] = i;
                /* fprintf(stderr, "primitive %d (%x) found at idx %x\n", i, primitives[i], idx); */
                break;
            }
        }
    }

    int pt_size = (char *)ptp - (char *)pt;
    im0 = add_primitive_table_block(im0, *image_size, pt_size, (char *)pt, image_size);

    free(primitives);
    free(pt);
    free(rt);

    return im0;
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
        fprintf(stderr, "image format error 2\n", idx+length, size);
        exit(2);
    }

    *block_type_out = block_type;
    *length_out = length;
    *offset_out = offset;

    /* fprintf(stderr, "next_block: idx: %d, block_type: %d, length: %d, offset: %d\n", */
    /*         idx, block_type, length, offset); */

    return idx;

}

cell *
load_evaluator_image(const char *image0, int image_size)
{
    char *image = malloc(image_size);
    cell size = *(cell *)image0;
    cell *e = NULL;
    int idx = sizeof(cell);
    cell block_type, length, offset;

    memcpy(image, image0, image_size);

    e = (cell *)malloc(size);

    int primitive_count = evaluate(NULL, NULL, 0, NULL);
    cell *primitives = malloc(primitive_count * sizeof(cell));

    primitive_count = evaluate(NULL, NULL, 0, primitives);

    while (idx < image_size) {

        idx = next_block(image, idx, image_size, &block_type, &length, &offset);

        cell *prp, *rtp;

        switch (block_type) {
        case bt_primitive_references:

            prp = (cell *)(image + idx);

            for (int pidx = 0; pidx < length/sizeof(cell); pidx++, prp++) {
                /* fprintf(stderr, "setting idx %x to primitive %d %x\n", pidx, ((cell *)image)[*prp], primitives[((cell *)image)[*prp]]); */
                ((cell *)image)[*prp] = primitives[((cell *)image)[*prp]];
            }

            break;

        case bt_relocation_table:

            rtp = (cell *)(image + idx);

            if (_from_ptr(e) == e)
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



__discard_all_diversions()dnl
