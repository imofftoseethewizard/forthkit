divert(`-1')
define(`__primitive', `divert(__primitive_declarations)$1,
divert(__primitive_implementations)case $1:')
define(`__end', `break;
')
define(`__declare_primitives', `enum {
undivert(__primitive_declarations) };

#define _pr_value(x)       ((cell)-x ## _token)
#define _pr_value_base     (-(number)pr_token_count + 1)
#define _pr_value_limit    -1

')
define(`__implement_evaluator_core', `
    do {
        _trace("start dispatch:     ");

        while (ip && !_is_primitive(*ip)) {
            _trace("dispatch execute:   ");
            *--rp = _from_ptr(ip+1);
            ip = _to_ptr(*ip);
        }

        _trace("dispatch primitive: ");
        if (ip) switch (*ip++) {
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
