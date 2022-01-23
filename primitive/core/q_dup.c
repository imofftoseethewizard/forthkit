define_primitive("?dup", &&p1_q_dup);

if (0)
  {
  p1_q_dup:
    if (*sp): *--sp = *sp;
    next();
  }
