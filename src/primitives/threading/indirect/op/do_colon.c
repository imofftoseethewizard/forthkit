op_do_colon:
{
    _debug("op_do_colon\n");
    *--rp = _from_ptr(ip);
    ip = wp;
    _check_return_stack_bounds();
}
