#define _c_half_cell_bits (8 * sizeof(cell) / 2))

#define _high_half(x) ((x) >> _c_half_cell_bits)
#define _low_half(x)  ((x) & (1 << _c_half_cell_bits - 1)

_primitive(pr_2_times) {
    if (sizeof(cell) < sizeof(void *))
        *(sp+1) = (*sp * *(sp+1));
    else {
        register cell a = *sp, b = *(sp+1);
        register cell high, mid, low;

        high = _high_half(a) * _high_half(b);
        low = _low_half(a) * _low_half(b);
        mid =
    }
    sp += 1;
    _next();
}
_define_primitive("2*", pr_2_times);
