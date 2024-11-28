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
