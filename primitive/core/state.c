define_primitive("STATE", pr_state);

//#define _state() *--sp = (cell)(&(e[ea_state]))
#define _state() *--sp = _ref_engine_attr(ea_state)
//
//#define _state() *--sp = ea_state

if (0) {
  pr_state:
    _debug("state: %lx %lx\n", (cell)&state, (cell)(&(e[ea_state])));
    _state();
    _next();
}
