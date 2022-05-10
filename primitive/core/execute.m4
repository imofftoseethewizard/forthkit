#define _execute(x) (*--rp = _from_ptr(ip), ip = _to_ptr(x))

__primitive(pr_execute)
{
    _execute(*sp++);
    _check_return_stack_bounds();
}
__end
__define_primitive("EXECUTE", pr_execute);
