divert(-1)
define(`__primitive', `divert(__primitive_registry)*prp++ = _from_pr($1);
divert(__primitive_implementations)    $1:')
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
        _print_stack();                   \
                                          \
        if (steps > 0) steps -= 1;        \
                                          \
        _trace("early main loop: ");      \
                                          \
        if (!_is_primitive(*ip))          \
            goto op_enter;                \
        else                              \
            goto *(cell *)_to_pv(*ip++);  \
    }                                     \
    while (1)

define(`__implement_evaluator_core', `
__first:

    if (0) {
        undivert(__primitive_implementations)

      op_end_fiber:
        {
            if (fp < fp0) {
                _debug("saving fiber %d\n", *fp);
                _print_registers();

                _save_fiber_state();
                fp++;
            }

            if (fp == fp0 || result)
                goto __last;

            _print_fiber_stack();
            _load_fiber_state();
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
