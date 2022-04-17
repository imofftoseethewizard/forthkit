#define _to_in() *--sp = _from_ptr(&e[ea_source_idx])

primitive(pr_to_in) {
    _to_in();
    _next();
}
