__primitive(pr_accept)
{
    register number n = (number)*sp++;
    register char *addr = (char *)_to_ptr(*sp++);
    register char *line = n > 0 ? readline(NULL) : NULL;
    register number len = line ? strlen(line) : 0;

    if (len)
        memcpy(addr, line, len);

    if (line)
        free(line);

    *--sp = len;
}
__end
__define_primitive("ACCEPT", pr_accept);
