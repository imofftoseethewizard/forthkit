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

    /*while (fp < fp0) {*/

        while (ip && !_debug_break()) {
            _trace("start dispatch:     ");

            _debug_count_step();

            if (!_is_primitive(*ip))
                _nest();
            else {
                _trace("dispatch primitive: ");
                switch (_to_pv(*ip++)) {
                undivert(__primitive_implementations)
                default:
                    ip = 0;
                    break;
                    /* illegal operator */
                }
            }
        }
/*        _join();
    }*/
    _trace("dispatch exited:   ");
')
divert`'dnl
