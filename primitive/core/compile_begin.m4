#define _compile_begin() *--sp = _from_ptr(here)

primitive(pr_compile_begin) {
    _compile_begin();
    _next();
}
