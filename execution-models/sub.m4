divert(`-1')
define(`__primitive', `divert(__primitive_declarations)auto void $1(void);
divert(__primitive_implementations)void $1(void)')
define(`__end', `')
define(`__declare_primitives', `undivert(__primitive_declarations)
')

divert(__header_definitions)

typedef void (native_word)(void);

#define _pr_value(x)        ((void *)&(x))
#define _pr_value_base      (void *)&engine
#define _pr_value_limit     __builtin_frame_address(0)

define(`__implement_evaluator_core', `undivert(__primitive_implementations)
while (fp < fp0) {
    while (ip && !_debug_break()) {
        if (!_is_primitive(*ip))
            _enter();
        else
            ((native_word *)(_to_pv(*ip++)))();
    }
    _save_fiber_state();
    fp++;
}
')
divert`'dnl
