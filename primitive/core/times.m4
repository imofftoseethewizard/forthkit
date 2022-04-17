#define _times() *++sp = (number)*(sp+1) * (number)*sp

primitive(pr_times) {
    _times();
    _next();
}
