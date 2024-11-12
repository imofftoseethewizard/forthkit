#define _enter()                  \
do {                              \
    *--rp = _from_ptr(ip+1);      \
    ip = wp;                      \
    _check_return_stack_bounds(); \
} while (0)
