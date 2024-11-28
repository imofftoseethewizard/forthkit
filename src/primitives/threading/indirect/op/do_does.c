op_do_does:
{
    *--rp = _from_ptr(ip+1);

    *--sp = _from_ptr(wp+1);
    ip = _to_ptr(*wp);

    _check_return_stack_bounds();
}
