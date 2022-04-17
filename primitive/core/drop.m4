#define _drop() ++sp

primitive(pr_drop) {
    _drop();
    _next();
}
