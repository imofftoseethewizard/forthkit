_primitive(pr_blk) {
    *--sp = _from_ptr(&e[ea_blk]);
    _next();
}
_define_primitive("BLK", pr_blk);
