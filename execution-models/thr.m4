divert(-1)
define(`__primitive', `divert(__primitive_implementations)    $1:')
define(`__end', `_next();
')
define(`__declare_primitives', `')

divert(__header_definitions)

#define _pr_value(x)       ((void *)&&x)
#define _pr_value_base     (void *)&&__first
#define _pr_value_limit    (void *)&&__last

#define _next()                     \
    do {                            \
        if (!ip || _debug_break())  \
            goto op_join;           \
                                    \
        _debug_count_step();        \
                                    \
        if (!_is_primitive(*ip))    \
            goto op_nest;           \
        else                        \
            goto *_to_pv(*ip++);    \
    }                               \
    while (1)

define(`__implement_evaluator_core', `
__first:

    if (0) {
        undivert(__primitive_implementations)

      op_join:
        {
            _join();

            if (fp == fp0)
                goto __last;
        }
        _next();

      op_nest:
        {
            _nest();
        }
        _next();
    }

    _next();

__last:
')
divert`'dnl
