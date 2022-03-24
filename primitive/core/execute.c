_primitive(pr_execute) {
    _trace("start execute: ");
    _execute(*sp++);
    _trace("end execute: ");
    _next();
}
