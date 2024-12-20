divert(`-1')
define(`__primitive', `divert(__primitive_registry)*prp++ = _from_pr($1);
divert(__primitive_declarations)$1,
divert(__primitive_implementations)case $1:')
define(`__end', `break;
')
define(`__declare_primitives', `enum {
primitive_start = c_msb,
undivert(__primitive_declarations)
primitive_count
};')

divert(__header_definitions)

#define _pr_value(x)       x
#define _pr_value_base     primitive_start
#define _pr_value_limit    primitive_count

define(`__implement_evaluator_core', `

    while (fp < fp0 && !result) {

        _print_fiber_stack();
        _load_fiber_state();

        _debug("loaded fiber %d\n", *fp);
        _print_registers();

        while (ip && steps && !result) {

            if (steps > 0) steps -= 1;

            _trace("early main loop: ");

            if (!_is_primitive(*ip))
                _enter();

            else {
                switch (_to_pv(*ip++)) {
                undivert(__primitive_implementations)
                default:
                    result = err_unknown_primitive;
                    ip = 0;
                    break;
                }
            }
            _check_parameter_stack_bounds();
            _print_stack();
       }

        if (fp < fp0) {
            _debug("saving fiber %d\n", *fp);
            _print_registers();

            _save_fiber_state();
            fp++;
        }
    }
')
divert`'dnl
