__primitive(pr_execute)
{
    /* EXECUTE ( addr -- )

       Execute the dictionary entry whose compilation address is on
       the stack.
     */

    if (_is_primitive(*sp))
        _pr_execute(*sp++);

    else {
        *--rp = _from_ptr(ip);
        ip = _to_ptr(*sp++);
    }

    _check_return_stack_bounds();
}
__end
__define_primitive("execute", pr_execute);
