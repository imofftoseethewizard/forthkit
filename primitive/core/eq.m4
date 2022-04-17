#define _eq() *(sp+1) = *(sp+1) == *sp, sp++

primitive(pr_eq) {
    _eq();
    _next();
}
