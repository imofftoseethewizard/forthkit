register_operator(ot_literal, &&op_literal);

/* op_literal pushes the next location onto the stack */
if (0) {
  op_literal:
    _debug("literal\n");
    *--sp = (cell)*ip++;
    print_stack(sp0, sp);
    _next();
}
