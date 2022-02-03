
#define _state() *--sp = (cell)_ref_engine_attr(ea_state)

_primitive(pr_state) {
    _state();
    _next();
}
define_primitive("STATE", pr_state);
