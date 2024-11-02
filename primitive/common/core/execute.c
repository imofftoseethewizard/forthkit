pr_execute:
{
    /* EXECUTE ( addr -- )

       Execute the dictionary entry whose compilation address is on
       the stack.
     */

    *--rp = _from_ptr(ip);
    ip = _to_ptr(*sp++);

    _check_return_stack_bounds();
}
