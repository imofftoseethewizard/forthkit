_declare_primitive(pr_buffer);

_primitive(pr_read_block) {

    register char *buffer = (char *)_to_ptr(*sp++);
    register cell n = *sp++;

    if (   storage_fd < 0
        || lseek(storage_fd, n*BUFFER_SIZE, SEEK_SET) == -1
        || read(storage_fd, buffer, BUFFER_SIZE) == -1
        ) {

        *--sp = -33;
        _abort();

    } else
        *--sp = _from_ptr(buffer);

    _next();
}

_compiled_word("BLOCK", 0) {
    _compile_pr(pr_dup);
    _compile_pr(pr_buffer);
    _compile_pr(pr_read_block);
    _compile_pr(op_exit);
}
