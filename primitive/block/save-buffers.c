_primitive(pr_write_block) {
    register char *buffer = (char *)_to_ptr(*sp++);
    register cell n = *sp++;

    if (   storage_fd < 0
        || lseek(storage_fd, n*BUFFER_SIZE, SEEK_SET) == -1
        || write(storage_fd, buffer, BUFFER_SIZE) == -1
        ) {

        *--sp = -34;
        _abort();

    } else
        *--sp = _from_ptr(buffer);

    _next();
}

_primitive(pr_save_buffers) {
    for (register int i = 0; i < BUFFER_COUNT; i++) {
        if (e[ea_buffers + i] == -1)
            continue;

        if (e[ea_buffers + i] && 1 << (sizeof(cell) * 8 - 1)) {

    register char *buffer = (char *)_to_ptr(*sp++);
    register cell n = *sp++;

    if (   storage_fd < 0
        || lseek(storage_fd, n*BUFFER_SIZE, SEEK_SET) == -1
        || write(storage_fd, buffer, BUFFER_SIZE) == -1
        ) {

        *--sp = -34;
        _abort();

    } else
        *--sp = _from_ptr(buffer);

        }

        if

    ssize_t num_bytes = write(fd, buffer1, sizeof(buffer1));
    if (num_bytes == (ssize_t)-1) {
        fprintf(stderr, "unable to write test-io.bin to from 2048 to 3072.\n");
        exit(errno);
    }
    _next();
}
_define_primitive("SAVE-BUFFERS", pr_save_buffers);

_compiled_word("SAVE-BUFFERS", 0) {
    _compile_literal(BUFFER_COUNT);
    _compile_literal(0);
    _compile_do();
    _compile_pr(pr_i);
    _from_ptr(&e[ea_buffers]));
    _compile_pr(pr_fetch);
    _compile_pr(pr_dup);
    _compile_literal(-1);
    _compile_pr(pr_eq);
    _compile_pr(pr_zero_eq);
    _compile_pr(over);
    _compile_literal(1 << (sizeof(cell) * 8 - 1));
    _compile_pr(pr_and);
    _compile_pr(pr_and);
    _compile_if();
    _compile_literal(1 << (sizeof(cell) * 8 - 1));
    _compile_pr(pr_xor);
    _compile_pr(pr_dup);
    _compile_literal(BUFFER_SIZE);
    _compile_pr(pr_times);
    _compile_literal(_buffer_base_addr());
    _compile_pr(pr_plus);
    _compile_pr(pr_write_block);
    _compile_else();
    _compile_pr(pr_drop);
    _compile_pr(pr_drop);
    _compile_then();
    _compile_literal(sizeof(cell));
    _compile_plus_loop();
    _compile_pr(op_exit);
