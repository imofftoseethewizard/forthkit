#define _key() *--sp = getc(stdin)

primitive(pr_key) {
    _key();
    _next();
}
