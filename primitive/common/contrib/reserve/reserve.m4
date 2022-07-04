#define _reserve(x) (((top -= (x) + ((int)top % sizeof(cell))) || 1) ? _from_ptr(top + sizeof(cell)) : 0)

__primitive(pr_reserve)
{
    *sp = _reserve(*sp);
}
__end

__define_primitive("reserve", pr_reserve);
