define_primitive("STATE", &&p1_state);

#define _state() *--sp = (cell)state

if (0) {
  p1_state:
     _state();
     _next();
}
