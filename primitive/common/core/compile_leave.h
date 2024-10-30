#define _compute_leave_jumps()                 \
do {                                           \
    register cell *np;                         \
                                               \
    while (leave_link != *sp) {                \
        np = _to_ptr(leave_link);              \
        leave_link = *np;                      \
        *np = dp - (char *)np;                 \
    }                                          \
    leave_link = *(sp+1);                      \
} while(0)
