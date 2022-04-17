#define _max() *++sp = (number)*(sp+1) < (number)*sp ? *sp : *(sp+1)

primitive(pr_max) {
    _max();
    _next();
}
