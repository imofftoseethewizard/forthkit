#define _min() *++sp = (number)*(sp+1) > (number)*sp ? *sp : *(sp+1)

primitive(pr_min) {
    _min();
    _next();
}
