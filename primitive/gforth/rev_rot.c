
#define _rev_rot() tmp0 = *sp, *sp = *(sp+1), *(sp+1) = *(sp+2), *(sp+2) = tmp0

if (0)
  {
  pr_rev_rot:
    _rev_rot();
    next();
  }
define_primitive("-ROT", pr_rev_rot);
