
#define _plus() *(number *)(sp+1) = (number)*(sp+1) + (number)*sp, sp++

_primitive(pr_plus) {
    _plus();
    _next();
}
_define_primitive("+", pr_plus);
