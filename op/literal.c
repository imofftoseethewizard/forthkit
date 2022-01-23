
/* op_literal pushes the next location onto the stack */
if (0)
  {
  op_literal:
    *--sp = (cell)*++ip;
    next();
  }
