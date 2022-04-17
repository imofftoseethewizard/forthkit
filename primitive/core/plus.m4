#define _plus() *(number *)(sp+1) = (number)*(sp+1) + (number)*sp, sp++

primitive(pr_plus) {
    _plus();
    _next();
}
