/* op_literal pushes the next location onto the stack */
_primitive(op_literal) {
    _debug("op literal: "); _print_stack();
    *--sp = (cell)*ip++;
    _next();
}

register_operator(ot_literal, op_literal);
