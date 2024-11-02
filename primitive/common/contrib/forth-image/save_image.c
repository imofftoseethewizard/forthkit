pr_save_image:
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

    register char *path = malloc(*sp + 1);
    register FILE *file = NULL;
    register cell
      *lenp = (cell *)dp,
      *addrp = (cell *)dp + 1;

    strncpy(path, (char *)_to_ptr(*(sp+1)), *sp);
    path[*sp] = 0;

    sp += 2;

    if (!path) {
        _abort(err_unable_to_allocate_memory);
        goto pr_save_image_exit;
    }

    file = fopen(path, "w");
    free(path);

    if (!file) {
        _abort(err_open_file);
        goto pr_save_image_exit;
    }

    /* ensure all register state is written to memory */
    _save_fiber_state();

    if (sizeof(cell) != fwrite(&e[ea_size], 1, sizeof(cell), file)) {
        _abort(err_write_file);
        goto pr_save_image_exit;
    }

    /* save task attributes */
    if (!write_image_block(bt_data, _task_area, e[ea_tasks],
                           (char *)_to_ptr(e[ea_tasks]), file)) {
        _abort(err_write_file);
        goto pr_save_image_exit;
    }

    /* save fiber attributes */
    if (!write_image_block(bt_data, _fiber_area, e[ea_fibers],
                           (char *)_to_ptr(e[ea_fibers]), file)) {
        _abort(err_write_file);
        goto pr_save_image_exit;
    }

    /* save task dictionaries (and engine attributes with task 0) */
    for (register int i = 0; i < e[ea_task_count]; i++) {

        register cell
          *t = _to_task_ptr(i),
          length = t[ta_dp] - t[ta_bottom];

        if (length == 0)
            continue;

        if (!write_image_block(bt_data, length, t[ta_bottom],
                               (char *)_to_ptr(t[ta_bottom]), file)) {
            _abort(err_write_file);
            goto pr_save_image_exit;
        }
    }

  pr_save_image_exit:

    if (file)
        fclose(file);
}
