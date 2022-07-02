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
    __declare_primitives()dnl

    static cell internal_primitives[] = {
        undivert(__primitive_registry)dnl
    };

    if (!evaluator) {
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

void
create_image_block(cell block_type, cell length, cell offset, char *data, cell *image)
{
    *image++ = block_type;
    *image++ = length;
    *image++ = offset;

    printf("create_image_block: block_type: %d, length: %d, offset: %d\n", block_type, length, offset);

    memcpy((char *)image, data, length);
}

int
image_block_size(int payload_size)
{
    return payload_size + 3 * sizeof(cell);
}

cell *
create_data_image(cell *e, int *image_size)
{
    /* save-image ( caddr u -- )

       Opens the file at the path given by caddr u, creating it if
       necessary.

       Saves the memory size of the evaluator and relevant sections
       of its memory as a list of blocks. The size is stored as a
       cell-sized value at the beginning of the file. This is
       followed by a sequence of blocks of the form.

       |   length
       |   address
       |   <length bytes>

       where length and address are cell-sized, and <length bytes>
       is the contents of the block.
     */

    char *image = malloc(e[ea_size]);
    char *imagep = image;
    char *data;

    if (!image)
        return NULL;

    *(cell *)imagep = e[ea_size];
    imagep += sizeof(cell);

    /* save task attributes */
    data = (char *)_to_ptr(e[ea_tasks]);
    create_image_block(bt_data, _task_area, (cell)(data - (char *)e), data, (cell *)imagep);
    imagep += image_block_size(_task_area);

    /* save fiber attributes */
    data = (char *)_to_ptr(e[ea_fibers]);
    create_image_block(bt_data, _fiber_area, (cell)(data - (char *)e), data, (cell *)imagep);
    imagep += image_block_size(_fiber_area);

    /* save task dictionaries (and engine attributes with task 0) */
    for (register int i = 0; i < e[ea_task_count]; i++) {
	register cell * t = _to_task_ptr(i), length = _align(t[ta_dp] - t[ta_bottom]);
        char *data = (char *)_to_ptr(t[ta_bottom]);

        if (length == 0)
            continue;

        create_image_block(bt_data, length, (cell)(data - (char *)e), data, (cell *)imagep);
        imagep += image_block_size(length);
    }

    *image_size = imagep - image;

    return realloc(image, *image_size);
}

cell *
create_evaluator_image(cell *e0, cell *e1, int *image_size)
{
    /* Implies relative addressing mode; there's no need for a relocation
     * table.
     */
    if (sizeof(cell) < sizeof(void *))
        return create_data_image(e0, image_size);

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
            printf("added relocation of %x with offset %x\n", idx * sizeof(cell), im0[idx]);
            *rtp++ = idx;
        }

    free(im1);

    int rt_size = (char *)rtp - (char *)rt;

    if (rt_size) {
        *image_size += image_block_size(rt_size);

        im1 = realloc(im0, *image_size);

        if (!im1) {
            free(im0);
            free(rt);
            *image_size = 0;
            return NULL;
        }

        im0 = im1;
        create_image_block(bt_relocation_table, rt_size, 0, (char *)rt, (char *)im0 + image_size0);
    }

    free(rt);

    printf("created image: size: %x\n", *(cell *)im0);

    return im0;
}

cell *
load_evaluator_image(const char *image0, int image_size)
{
    char *image = malloc(image_size);
    cell size = *(cell *)image0;
    cell *evaluator = NULL;
    int idx = sizeof(cell);
    cell block_type, length, offset;

    memcpy(image, image0, image_size);

    printf("size: %x\n", size);
    evaluator = (cell *)malloc(size);
    printf("evaluator: %x, evaluator + size: %x\n", evaluator, (char *)evaluator + size);

    int primitive_count = evaluate(NULL, NULL, 0, NULL);
    cell *primitives = malloc(primitive_count * sizeof(cell));

    primitive_count = evaluate(NULL, NULL, 0, primitives);

    printf("image_size: %d\n", image_size);
    while (idx < image_size) {

        if (idx + 3 * sizeof(cell) >= image_size) {
            fprintf(stderr, "image format error 1");
            exit(2);
        }

        block_type = *(cell *)(image + idx);
        idx += sizeof(cell);

        length = *(cell *)(image + idx);
        idx += sizeof(cell);

        offset = *(cell *)(image + idx);
        idx += sizeof(cell);

        printf("block_type: %d, length: %d, offset: %d, idx + length: %d\n", block_type, length, offset, idx + length);

        if (idx + length > image_size) {
            fprintf(stderr, "image format error 2");
            exit(2);
        }

        cell *rtp = (cell *)(image + idx);
        if (block_type == bt_relocation_table)
            for (int ridx = 0; ridx < length/sizeof(cell); ridx++, rtp++) {
                printf("relocating cell at %x from %x to %x\n", *rtp, ((cell *)image)[*rtp], ((cell *)image)[*rtp] + (cell)evaluator);
                ((cell *)image)[*rtp] += (cell)evaluator;
            }

        idx += length;
    }

    idx = sizeof(cell);
    while (idx < image_size) {

        if (idx + 3 * sizeof(cell) >= image_size) {
            fprintf(stderr, "image format error 1");
            exit(2);
        }

        block_type = *(cell *)(image + idx);
        idx += sizeof(cell);

        length = *(cell *)(image + idx);
        idx += sizeof(cell);

        offset = *(cell *)(image + idx);
        idx += sizeof(cell);

        printf("block_type: %d, length: %d, offset: %d, idx + length: %d\n", block_type, length, offset, idx + length);

        if (idx + length > image_size) {
            fprintf(stderr, "image format error 2");
            exit(2);
        }

        printf("(char *)evaluator + offset: %x, image + idx: %x, length: %d);\n", (char *)evaluator + offset, image + idx, length);
        if (block_type == bt_data)
            memcpy((char *)evaluator + offset, image + idx, length);

        idx += length;
    }

    free(image);

    printf("image loaded\n");
    return evaluator;
}



__discard_all_diversions()dnl
