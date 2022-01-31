
#define _store() *(cell *)*sp = *(sp+1), sp += 2

_primitive(pr_store) {
    _store();
    _next();
}
define_primitive("!", pr_store);
