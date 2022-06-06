#ifdef BOUNDS_CHECKING

#define _check_buffer_address(x)

#define _check_dictionary_bounds()                   \
do {                                                 \
    if (dp >= top)                                   \
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

#define _is_active_fiber_number(x) ((x) == *fp)
#define _is_fiber_stack_full() (fp0 - fp == e[ea_fiber_stack_size])
#define _is_valid_fiber_number(x) ((cell)(x) < e[ea_fiber_count])

#define _is_active_task_number(x) ((x) == _to_fiber_ptr(*fp)[fa_task])
#define _is_primary_task_number(x) ((x) == _primary_task)
#define _is_valid_task_number(x) ((cell)(x) < e[ea_task_count])

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

#define _is_active_fiber_number() 0
#define _is_fiber_stack_full() 0
#define _is_valid_fiber_number() 1

#define _is_active_task_number(x) 0
#define _is_primary_task_number(x) 0
#define _is_valid_task_number(x) 1

#endif
