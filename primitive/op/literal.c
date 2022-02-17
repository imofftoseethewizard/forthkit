#define _compile_literal(x) do { _compile_pr(op_literal); _store_data(x); } while (0)

/* op_literal pushes the next location onto the stack */
_primitive(op_literal) {
    *--sp = (cell)*ip++;
    _next();
}

_register_operator(ot_literal, op_literal);
