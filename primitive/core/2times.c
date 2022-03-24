/* requires including double_number.h */
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
