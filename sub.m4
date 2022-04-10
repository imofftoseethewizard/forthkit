include(`preamble.m4')
define(`primitive', `divert(1)auto void $1(void);
divert(2)void $1(void)')dnl
define(`declare_primitives', `undivert(1)')dnl
define(`implement_evaluator_core', `implement_primitives()
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
