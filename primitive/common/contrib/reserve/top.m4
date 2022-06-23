#define _top() *--sp = _from_ptr(top)

__primitive(pr_top)
{
    _top();
}
__end

__define_primitive("top", pr_top);
