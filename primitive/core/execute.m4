#define _execute(x) (*--rp = _from_ptr(ip), ip = _to_ptr(x))

__primitive(pr_execute)  
{
    _trace("start execute: ");
    _execute(*sp++);
    _trace("end execute: ");
}
__end
__define_primitive("EXECUTE", pr_execute);
