divert(`-1')
define(`__primitive', `divert(__primitive_declarations)$1,
divert(__primitive_implementations)case $1:')
define(`__end', `break;
')
define(`__declare_primitives', `enum {
undivert(__primitive_declarations)
primitive_count
};')

divert(__header_definitions)

#define _pr_value(x)       x
#define _pr_value_base     0
#define _pr_value_limit    -1

define(`__implement_evaluator_core', `
    do {
        _trace("start dispatch:     ");

        while (ip && !_is_primitive(*ip)) {
            _trace("dispatch execute:   ");
            *--rp = _from_ptr(ip+1);
            ip = _to_ptr(*ip);
        }

        _trace("dispatch primitive: ");
        if (ip) switch (_to_pv(*ip++)) {
        undivert(__primitive_implementations)
        default:
          ip = 0;
        break;
          /* illegal operator */
        }
    }
    while (ip);

    _trace("dispatch exited:   ");
')
divert`'dnl
