_primitive(pr_expect) {
    register number n = (number)*sp++;
    register char *addr = (char *)_to_ptr(*sp++);
    register char *line = n > 0 ? readline(NULL) : NULL;
    register int len = line ? strlen(line) : 0;

    len = len > n-1 ? n-1 : len;

    if (len)
        memcpy(addr, line, len);

    if (line) {
        addr[len] = 0;
        free(line);
    }

}
