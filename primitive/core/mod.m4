#define _mod() *++sp = (number)*(sp+1) % (number)*sp

primitive(pr_mod) {
    _mod();
    _next();
}
