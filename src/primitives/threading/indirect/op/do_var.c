op_do_var:
{
    _debug("op_do_var: %x %x %x\n", *(wp-1), *wp, *(wp+1));
    *--sp = wp;
}
