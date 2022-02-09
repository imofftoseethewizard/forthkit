
#define _store_compiled(x) _store_data(_get_word_interpretation(x));

_primitive(pr_store_compiled) {
    _store_compiled(*sp++);
    _next();
}

_define_primitive("COMPILE,", pr_store_compiled);
