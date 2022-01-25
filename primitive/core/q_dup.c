define_primitive("?DUP", &&pr_q_dup);

if (0)
  {
  pr_q_dup:
    if (*sp): *--sp = *sp;
    _next();
  }
