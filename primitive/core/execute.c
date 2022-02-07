/* _execute is defined in machine.c */

_primitive(pr_execute) {
    _trace("start execute: ");
    _execute(*sp++);
    _trace("end execute: ");
    _next();
}
_define_primitive("EXECUTE", pr_execute);
