#define _execute(x) (*--rp = _from_ptr(ip), ip = _to_ptr(x))

_primitive(pr_execute) {
    _trace("start execute: ");
    _execute(*sp++);
    _trace("end execute: ");
    _next();
}
_define_primitive("EXECUTE", pr_execute);
