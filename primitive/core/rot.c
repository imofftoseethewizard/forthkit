define_primitive("rot", &&p1_rot);

#define _rot() tmp0 = *sp, *sp = *(sp+2), *(sp+2) = *(sp+1), *(sp+1) = tmp0

if (0)
  {
  p1_rot:
    _rot();
    next();
  }
