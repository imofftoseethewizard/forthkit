include(`preamble.m4')
define(`primitive', `divert(2)if (0) $1:')
define(`declare_primitives', `')dnl
define(`implement_evaluator_core', `implement_primitives()
    _next();')
