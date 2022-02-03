/* op_exit pops the top of the return stack into ip and advances
   it past the call to the just completed word.
*/
_primitive(op_exit) {
    _print_return_stack();
    ip = *rp ? _to_native_ptr(*rp) : 0;
    rp++;
    _next();
}

register_operator(ot_exit, op_exit);
