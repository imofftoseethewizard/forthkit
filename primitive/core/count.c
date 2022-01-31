
#define _count() *(sp-1) = *(length_type *)*sp, *sp-- = (cell)((length_type *)*sp + 1)

_primitive(pr_count) {
    _count();
    _next();
}
define_primitive("COUNT", pr_count);
