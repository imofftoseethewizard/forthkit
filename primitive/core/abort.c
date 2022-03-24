_primitive(pr_abort) {
     /* -1 is the throw code for abort.
        see https://forth-standard.org/standard/exception
     */
    *--sp = -1;
    _abort();
    _next();
}
