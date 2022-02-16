/* Note that this abort is functionally distinct from the abort word.
 */
#define _abort() result = *sp, sp = sp0, rp = rp0, ip = 0, e[ea_state] = 0

_primitive(op_abort) {
    _abort();
    _next();
}

_register_operator(ot_abort, op_abort);
