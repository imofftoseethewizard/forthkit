#define _compile_while()          \
    do {                          \
        _compile_pw(op_0branch);  \
        *--sp = _from_ptr(dp);    \
        _store_data(0);           \
        _swap();                  \
    } while (0)
