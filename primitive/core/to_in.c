#define _to_in() *--sp = _from_ptr(&e[ea_source_idx])

_primitive(pr_to_in) {
    _to_in();
    _next();
}
_define_primitive(">IN", pr_to_in);
