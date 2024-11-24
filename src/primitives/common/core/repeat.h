#define _compile_repeat()                               \
do {                                                    \
    _compile_pw(op_jump);                               \
    _store_data(*sp++ - _from_ptr(dp));                 \
    _compile_jump_target();                             \
} while (0);
