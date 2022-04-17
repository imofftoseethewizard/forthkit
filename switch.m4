include(`preamble.m4')dnl
define(`primitive', `divert(primitive_declarations)$1,
divert(primitive_implementations)case $1:')dnl
define(`declare_primitives', `enum {
        undivert(primitive_declarations)
    };')dnl
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
        undivert(primitive_implementations)
        default:
          ip = 0;
        break;
          /* illegal operator */
        }
    }
    while (ip);

    _trace("dispatch exited:   ");')dnl
