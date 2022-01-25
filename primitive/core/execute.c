define_primitive("EXECUTE", &&p1_execute);

/* _execute is defined in machine.c */

if (0) {
  p1_execute:
     _execute(*sp++);
     _next();
}
