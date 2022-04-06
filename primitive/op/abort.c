/* Note that this abort is functionally distinct from the abort word.
 */
_primitive(op_abort) {
    _abort();
    _next();
}

_register_operator(ot_abort, op_abort);
