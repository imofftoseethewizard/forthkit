define_primitive(">=", &&p1_gt_eq);

#define _gt_eq() *++sp = *(sp+1) >= *sp

if (0)
  {
  p1_gt_eq:
    _gt_eq();
    next();
  }
