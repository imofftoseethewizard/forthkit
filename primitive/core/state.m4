#define _state() *--sp = _from_ptr(&e[ea_state])

primitive(pr_state) {
    _state();
    _next();
}
