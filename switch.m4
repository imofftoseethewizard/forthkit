include(`preamble.m4')
define(`primitive', `divert(1)$1,
divert(2)case $1:')dnl
define(`declare_primitives', `enum {
        undivert(1)
    };')
define(`implement_evaluator_core', `
    do {
        _trace("start dispatch:     ");

        while (ip && !_is_primitive(*ip)) {
            _trace("dispatch execute:   ");
            *--rp = _from_ptr(ip+1);
            ip = _to_ptr(*ip);
        }

        _trace("dispatch primitive: ");
        if (ip) switch (*ip++) {
        implement_primitives()
        default:
          ip = 0;
        break;
          /* illegal operator */
        }
    }
    while (ip);

    _trace("dispatch exited:   ");')
