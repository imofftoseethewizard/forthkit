define_primitive("!", pr_store);

#define _store() *(cell *)*sp = *(sp+1), sp += 2

if (0) {
  pr_store:
    _store();
    _next();
}
