define_primitive("STATE", pr_state);

#define _state() *--sp = (cell)_ref_engine_attr(ea_state)

if (0) {
  pr_state:
    _state();
    _next();
}
