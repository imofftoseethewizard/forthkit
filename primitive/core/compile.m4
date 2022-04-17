primitive(pr_compile) {
    *(cell *)here = *ip++;
    _next();
}
