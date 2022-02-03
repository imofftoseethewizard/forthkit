
/* _execute is defined in machine.c */

_primitive(pr_execute) {
    _debug("execute: ");
    print_stack(sp0, sp);
    _execute(*sp++);
    _next();
}
define_primitive("EXECUTE", pr_execute);
