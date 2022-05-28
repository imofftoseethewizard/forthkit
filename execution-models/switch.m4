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
#define _pr_value_limit    primitive_count

define(`__implement_evaluator_core', `

    while (fp < fp0 && !result) {

        _load_fiber_state();

        while (ip && steps && !result) {

            if (steps > 0) steps -= 1;

            _trace("early main loop: ");

            if (!_is_primitive(*ip))
                _enter();

            else {
                switch (_to_pv(*ip++)) {
                undivert(__primitive_implementations)
                default:
                    printf("e: %x\n", e);
                    printf("_pr_value_base: %x\n", _pr_value_base);
                    printf("_pr_value_limit: %x\n", _pr_value_limit);
                    printf("*ip: %x\n", *(ip-1));
                    result = err_unknown_primitive;
                    ip = 0;
                    break;
                }
            }
            _check_parameter_stack_bounds();
        }

       if (fp < fp0) {
           _save_fiber_state();
           fp++;
       }
    }
')
divert`'dnl
