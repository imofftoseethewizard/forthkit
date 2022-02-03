/* op_exit pops the top of the return stack into ip and advances
   it past the call to the just completed word.
*/
_primitive(op_exit) {
    print_return_stack(rp0, rp);
    ip = *rp ? _to_native_ptr(*rp) : 0;
    rp++;
    _next();
}

register_operator(ot_exit, op_exit);
