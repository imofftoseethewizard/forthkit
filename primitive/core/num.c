#define _digit(x) ((x) <= 9 ? '0' + (x) : 'a' + (x) - 10)

_primitive(pr_num) {
    _hold(_digit(*sp % e[ea_base]));
    *sp /= e[ea_base];
    _next();
}
_define_primitive("#", pr_num);
