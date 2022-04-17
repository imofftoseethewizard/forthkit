#define _execute(x) (*--rp = _from_ptr(ip), ip = _to_ptr(x))

primitive(pr_execute) {
    _trace("start execute: ");
    _execute(*sp++);
    _trace("end execute: ");
    _next();
}
