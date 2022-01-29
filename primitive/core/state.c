define_primitive("STATE", &&pr_state);

#define _state() *--sp = (cell)&state

if (0) {
  pr_state:
    _state();
    _debug("state: %lx **sp: %lx \n", state, *(cell *)*sp);
    _next();
}
