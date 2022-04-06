/* op_exit pops the top of the return stack into ip and advances
   it past the call to the just completed word.
*/

_primitive(op_exit) {
    _trace("start exit: ");
    _exit();
    _trace("end exit: ");
    _next();
}

_register_operator(ot_exit, op_exit);
