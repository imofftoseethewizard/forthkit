divert(`-1')
define(`__primitive', `divert(__primitive_declarations)auto void $1(void);
divert(__primitive_implementations)void $1(void)')
define(`__end', `')
define(`__declare_primitives', `undivert(__primitive_declarations)
')

#define _pr_value(x)        ((void *)&(x))
#define _pr_value_base      (void *)&engine
#define _pr_value_limit     __builtin_frame_address(0)

define(`__implement_evaluator_core', `undivert(__primitive_implementations)
do {
        _trace("start dispatch:     ");

        while (ip && !_is_primitive(*ip)) {
            _trace("dispatch execute:   ");
            *--rp = _from_ptr(ip+1);
            ip = _to_ptr(*ip);
        }

        _trace("dispatch primitive: ");
        if (ip) ((native_word *)(_to_pv(*ip++)))();
    }
    while (ip);

    _trace("dispatch exited:   ");
')
divert`'dnl
