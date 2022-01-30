define_primitive("EXECUTE", pr_execute);

/* _execute is defined in machine.c */

if (0) {
  pr_execute:
    _execute(*sp++);
    _next();
}
