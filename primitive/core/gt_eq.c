
#define _gt_eq() *++sp = *(sp+1) >= *sp

_primitive(pr_gt_eq) {
    _gt_eq();
    _next();
}
define_primitive(">=", pr_gt_eq);
