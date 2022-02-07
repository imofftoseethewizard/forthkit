#define _c_number_pad_size 2 * sizeof(cell) * 8 + 2

#define _digit(x) ((x) <= 9 ? '0' + (x) : 'a' + (x) - 10)

_primitive(pr_num) {
    register length_type *idx = (length_type *)here;
    *(here + sizeof(length_type) + --(*idx)) = _digit(*sp % e[ea_base]);
    *sp /= e[ea_base];
    _next();
}
_define_primitive("#", pr_num);
