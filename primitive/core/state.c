#define _state() *--sp = _from_native_ptr(&e[ea_state])

_primitive(pr_state) {
    _state();
    _next();
}
define_primitive("STATE", pr_state);
