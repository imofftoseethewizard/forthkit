#define _compile_until()                                      \
    do {                                                      \
        _compile_pr(op_0branch);                              \
        _store_data(*sp++ - _from_ptr(dp));  \
    } while (0);
