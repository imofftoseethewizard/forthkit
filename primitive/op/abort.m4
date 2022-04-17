#define _abort() result = *sp, sp = sp0, rp = rp0, ip = 0, e[ea_state] = 0

primitive(pr_abort) {
     /* -1 is the throw code for abort.
        see https://forth-standard.org/standard/exception
     */
    *--sp = -1;
    _abort();
    _next();
}
