_primitive(pr_type) {
    if ((long)*sp > 0)
        fwrite(_to_ptr(*(sp+1)), sizeof(char), *sp, stdout);
    sp += 2;
}
_define_primitive("TYPE", pr_type);
