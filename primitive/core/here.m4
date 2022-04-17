#define _here() *--sp = _from_ptr(here)

primitive(pr_here) {
    _here();
    _next();
}
