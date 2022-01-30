define_primitive("ROT", pr_rot);

#define _rot() tmp0 = *sp, *sp = *(sp+2), *(sp+2) = *(sp+1), *(sp+1) = tmp0

if (0) {
  pr_rot:
    _rot();
    _next();
}
