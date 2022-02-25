_primitive(pr_store_data) {
    _store_data(*sp++);
    _next();
}
_define_primitive(",", pr_store_data);
