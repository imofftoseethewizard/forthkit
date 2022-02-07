#define _c_half_cell_bits (8 * sizeof(cell) / 2))

#define _high_half(x) ((x) >> _c_half_cell_bits)
#define _low_half(x)  ((x) & (1 << _c_half_cell_bits - 1)

_primitive(pr_times_div) {
    if (sizeof(cell) < sizeof(long))
        *(sp+2) = (cell)(((long)*(sp+2) * (long)*(sp+1)) / *sp);
    else {
        *(char *)0;
    }
    sp -= 2;
    _next();
}
_define_primitive("*/", pr_times_div);
