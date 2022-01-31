
#define _state() *--sp = (cell)&state

_primitive(pr_state) {
    _state();
    _next();
}
define_primitive("STATE", pr_state);
