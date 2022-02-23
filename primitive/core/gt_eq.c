#define _gt_eq() *++sp = (number)*(sp+1) >= (number)*sp

_primitive(pr_gt_eq) {
    _gt_eq();
    _next();
}
_define_primitive(">=", pr_gt_eq);
