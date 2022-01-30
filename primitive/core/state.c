define_primitive("STATE", pr_state);

#define _state() *--sp = (cell)&state

if (0) {
  pr_state:
    _state();
    _next();
}
