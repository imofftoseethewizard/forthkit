#define _fetch() *sp = *_to_ptr(*sp)

primitive(pr_fetch) {
    _fetch();
    _next();
}
