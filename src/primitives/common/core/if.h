#define _compile_if()             \
    do {                          \
        _compile_pw(op_0branch);  \
        *--sp = _from_ptr(dp);    \
        _store_data(0);           \
    } while (0)
