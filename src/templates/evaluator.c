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

	static void bootstrap_evaluator(cell *e);
    static int evaluate(cell *evaluator, const char *source, int storage_fd, cell *primitives);

/*{ init_evaluator }*/

	int
	evaluate_source(cell *evaluator, const char *source, int storage_fd)
	{
		if (!evaluator)
			return 0;

		return evaluate(evaluator, source, storage_fd, NULL);
	}

	void
	bootstrap_evaluator(cell *e)
	{
		/* signals to evaluate() that the evaluator's memory is uninitialized */
		e[ea_top] = 0;

		/* trigger bootstrap */
		evaluate(e, "", -1, NULL);
	}

int
evaluate(cell *evaluator, const char *source, int storage_fd, cell *primitives)
{
	/*{ declare_primitives }*/

	static cell internal_primitives[/*{ primitive_count }*/];

    int result = 0;

    register cell *e = evaluator;

    register char *top;

    register cell *rp0;
    register cell *sp0;

    register char *dp;
    register cell *sp;

    register cell *ip;
    register cell *rp;

	/*{ evaluator_variables }*/

    if (!evaluator) {

	    if (primitives) {

		    cell *prp = primitives;

		    /*{ initialize_primitive_registry }*/
	    }

	    return /*{ primitive_count }*/;
    }

#ifdef BOOTSTRAP
    if (!e[ea_top]) {

	    /*{ begin_bootstrap }*/

        /*{ primitive_word_definitions }*/

        /*{ compiled_word_definitions }*/

	    const char *library_word_definitions[] = {
		    /*{ library_word_definitions }*/
	    };

	    for (int i = 0; i < /*{ library_word_count }*/; i++) {

		    result = evaluate(evaluator, library_word_definitions[i], -1, NULL);

		    if (result)
			    break;
	    }

	    /*{ finish_bootstrap }*/

	    return result;
    }
#endif

    _debug("interpreting source '%s'\n", source);

    /* copy source into evaluator memory */

    memcpy(_to_ptr(e[ea_source_addr]), source, e[ea_source_len] = strlen(source));
    e[ea_source_idx] = 0;

    /*{ evaluator_core }*/

    _debug("done with run: result: %d\n", result);
    _print_stack();

    return result;
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

/*{ create_data_image }*/

cell *
create_relocation_table(cell *e0, cell *e1, cell *im0, cell *im1, int image_size, int *rt_size_out)
{
    /* relocation table */
    cell *rt = malloc(image_size), *rtp = rt;

    *rt_size_out = 0;

    if (!rt)
        return NULL;

    /* If the evaluators use relocatable addressing, then they should be
     * identical. If they use absolute addressing, then they will differ
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

	cell *pt = malloc(image_size - rt_size);
	cell *ptp = pt;

    /* Get the evaluator's list of primitives. */

    cell *primitives = malloc(/*{ primitive_count }*/ * sizeof(cell));
    evaluate(NULL, NULL, -1, primitives);

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

    cell *primitives = malloc(/*{ primitive_count }*/ * sizeof(cell));
    int primitive_count = evaluate(NULL, NULL, -1, primitives);

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

    free(primitives);
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
