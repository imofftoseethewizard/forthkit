#define _gt_eq() *++sp = (number)*(sp+1) >= (number)*sp

__primitive(pr_gt_eq)  
{
    _gt_eq();
}
__end
__define_primitive(">=", pr_gt_eq);
