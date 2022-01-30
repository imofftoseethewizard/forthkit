define_primitive("?DUP", pr_q_dup);

if (0) {
  pr_q_dup:
    if (*sp) *--sp = *(sp+1);
    _next();
}
