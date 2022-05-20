#define _reserve(x) (((e[ea_top] -= (x)) || 1) ? _from_ptr((char *)e + e[ea_top] + sizeof(cell)) : 0)

__primitive(pr_reserve)
{
    *sp = _reserve(*sp);
}
__end

__define_primitive("reserve", pr_reserve);
