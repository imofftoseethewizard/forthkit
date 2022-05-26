divert(-1)
define(`__primitive', `divert(__primitive_implementations)    $1:')
define(`__end', `_next();
')
define(`__declare_primitives', `')

divert(__header_definitions)

#define _pr_value(x)       ((void *)&&x)
#define _pr_value_base     (void *)&&__first
#define _pr_value_limit    (void *)&&__last

#define _next()                           \
    do {                                  \
        if (!ip || !steps || result )     \
            goto op_end_fiber;            \
                                          \
        _check_parameter_stack_bounds();  \
                                          \
        if (steps > 0) steps -= 1;        \
                                          \
        if (!_is_primitive(*ip))          \
            goto op_enter;                \
        else                              \
            goto *_to_pv(*ip++);          \
    }                                     \
    while (1)

define(`__implement_evaluator_core', `
__first:

    if (0) {
        undivert(__primitive_implementations)

      op_end_fiber:
        {
            _save_fiber_state();
            fp++;

            if (fp == fp0 || result)
                goto __last;
        }
        _next();

      op_enter:
        {
            _enter();
        }
        _next();
    }

    _next();

__last:
')
divert`'dnl
