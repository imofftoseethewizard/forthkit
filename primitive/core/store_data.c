
_primitive(pr_store_data) {
    _store_data(*sp++);
    _next();
}
define_primitive(",", pr_store_data);
