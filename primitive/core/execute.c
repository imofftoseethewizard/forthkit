
/* _execute is defined in machine.c */

_primitive(pr_execute) {
    _debug("execute: ");
    _print_stack();
    _execute(*sp++);
    _next();
}
define_primitive("EXECUTE", pr_execute);
