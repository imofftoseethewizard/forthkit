_primitive(pr_c_store) {
    *(char *)_to_ptr(*sp) = (char)*(sp+1);
    sp += 2;
    _next();
}
_define_primitive("C!", pr_c_store);
