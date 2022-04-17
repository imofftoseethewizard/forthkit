include(`preamble.m4')
define(`primitive', `divert(primitive_declarations)auto void $1(void);
divert(primitive_implementations)void $1(void)')dnl
define(`declare_primitives', `undivert(primitive_declarations)')dnl
define(`implement_evaluator_core', `undivert(primitive_implementations)
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

    _trace("dispatch exited:   ");')
