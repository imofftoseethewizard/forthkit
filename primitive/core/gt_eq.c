define_primitive(">=", pr_gt_eq);

#define _gt_eq() *++sp = *(sp+1) >= *sp

if (0) {
  pr_gt_eq:
    _gt_eq();
    _next();
}
