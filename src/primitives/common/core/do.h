/*|

`_store_data(0)` below reserves space for the relative addr of the
first code cell after the end of the loop, to be filled in by `LOOP`
or `+LOOP`.

  |*/
#define _compile_do()                \
    do {                             \
        _compile_pw(op_do);         \
        _store_data(0);              \
        *--sp = _from_ptr(dp);       \
    } while (0)
