register_operator(ot_literal, op_literal);

/* op_literal pushes the next location onto the stack */
_primitive(op_literal) {
    *--sp = (cell)*ip++;
    _next();
}
