define_primitive("?DUP", &&p1_q_dup);

if (0)
  {
  p1_q_dup:
    if (*sp): *--sp = *sp;
    _next();
  }
