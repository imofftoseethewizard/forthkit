#define _store() *_to_ptr(*sp) = *(sp+1), sp += 2

primitive(pr_store) {
    _store();
    _next();
}
