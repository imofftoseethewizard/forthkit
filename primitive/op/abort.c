/* Note that this abort is functionally distinct from the abort word.
 */
#define _abort() sp = sp0, rp = rp0, ip = 0, result = 1

_primitive(op_abort) {
    _abort();
    _next();
}

register_operator(ot_abort, op_abort);
