#define _state() *--sp = _from_ptr(&e[ea_state])

_primitive(pr_state) {
    _state();
    _next();
}
_define_primitive("STATE", pr_state);
