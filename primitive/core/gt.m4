#define _gt() *++sp = (number)*(sp+1) >  (number)*sp

primitive(pr_gt) {
    _gt();
    _next();
}
