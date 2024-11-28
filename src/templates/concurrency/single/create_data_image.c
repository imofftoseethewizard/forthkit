cell *
create_data_image(cell *e, int *image_size)
{
    cell *image = malloc(sizeof(cell));

    if (!image)
        return NULL;

    *image = e[ea_size];
    *image_size = sizeof(cell);

    register cell length = _align(e[ea_dp] - e[ea_bottom]);
    char *data = (char *)_to_ptr(e[ea_bottom]);

    image = add_data_block(
        image, *image_size, length, (cell)(data - (char *)e), data, image_size);

    return realloc(image, *image_size);
}
