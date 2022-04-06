/* op_jump expects the next location to be an offset. It is relative
   to where the ip would normally be next, hence the `+ 2` to account
   for advancing past op_jump and the offset.
*/

_primitive(op_jump) {
    _debug("jump: *ip: %lx, %ld\n", (long)*ip, (long)*ip);
    ip = (cell *)((char *)ip + (number)*ip - sizeof(cell));
    _debug("jump: *ip: %lx\n", (long)*ip);
    _next();
}

_register_operator(ot_jump, op_jump);
