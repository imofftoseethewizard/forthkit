#ifdef BOUNDS_CHECKING

#define _check_buffer_address(x)

#define _check_dictionary_bounds()                   \
do {                                                 \
    if (_from_ptr(dp) >= e[ea_top])                  \
        _abort(err_dictionary_overflow);             \
} while (0)

#define _check_fiber_stack_bounds()                  \
do {                                                 \
    if (fp < fp0 - e[ea_fiber_stack_size])           \
        _abort(err_fiber_stack_overflow);            \
    else if (fp > fp0)                               \
        _abort(err_fiber_stack_underflow);           \
} while (0)

#define _check_loader_context_stack_bounds()

#define _check_parameter_stack_bounds()              \
do {                                                 \
    if (sp > sp0)                                    \
        _abort(err_parameter_stack_underflow);       \
    else if (sp < sp0 - e[ea_parameter_stack_size])  \
        _abort(err_parameter_stack_overflow);        \
} while (0)

#define _check_return_stack_bounds()                 \
do {                                                 \
    if (rp > rp0)                                    \
        _abort(err_return_stack_underflow);          \
    else if (rp < rp0 - e[ea_return_stack_size])     \
        _abort(err_return_stack_overflow);           \
} while (0)

#define _check_task_address(t)
#define _check_task_memory()
#define _check_thread_memory()

#else

#define _check_buffer_address()
#define _check_dictionary_bounds()
#define _check_fiber_stack_bounds()
#define _check_loader_context_stack_bounds()
#define _check_parameter_stack_bounds()
#define _check_return_stack_bounds()
#define _check_task_address()
#define _check_task_memory()
#define _check_thread_memory()

#endif
