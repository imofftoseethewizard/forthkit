include(`errors.m4')dnl
dnl
__define_error_symbols();

extern const char *error_message(number code);
extern int error_code(const char *symbol);
