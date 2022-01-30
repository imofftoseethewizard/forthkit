define_primitive("PICK", pr_pick);

#define _pick() *sp-- = *(sp + 1 + *(sp+1))

if (0) {
  pr_pick:
    _pick();
    _next();
}
