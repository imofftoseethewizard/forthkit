define_primitive("COMPILE,", &&pr_store_compiled);

#define _store_compiled(x) _store_data(_get_word_interpretation_semantics(x));

if (0) {
  pr_store_compiled:
    _store_compiled(*sp++);
    _next();
}
