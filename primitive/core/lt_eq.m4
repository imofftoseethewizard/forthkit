#define _lt_eq() *++sp = (number)*(sp+1) <= (number)*sp

primitive(pr_lt_eq) {
    _lt_eq();
    _next();
}
_define_primitive("<=", pr_lt_eq);
