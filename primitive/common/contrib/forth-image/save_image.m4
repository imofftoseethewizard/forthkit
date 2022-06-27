__primitive(pr_save_image)
{
    /* save-image ( caddr u -- )

       Opens the file at the path given by caddr u, creating it if
       necessary. The entirety of the memory available to the
       interpreter is saved as is.
     */

    register char *path = malloc(*sp + 1);
    register FILE *file = NULL;
    register int bytes_written = -1;

    strncpy(path, (char *)_to_ptr(*(sp+1)), *sp);
    path[*sp] = 0;

    sp += 2;

    file = fopen(path, "w");

    if (file) {
        bytes_written = fwrite(e, 1, e[ea_size], file);
        fclose(file);
    }

    if (!file)
        _abort(err_open_file);

    else if (bytes_written < e[ea_size])
        _abort(err_write_file);
}
__end
__define_primitive("save-image", pr_save_image);
