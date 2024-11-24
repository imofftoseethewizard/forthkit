#define _compile_until()                                      \
    do {                                                      \
        _compile_pw(op_0branch);                              \
        _store_data(*sp++ - _from_ptr(dp));  \
    } while (0);
