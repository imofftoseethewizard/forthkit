register_operator(ot_exit, op_exit);

/* op_exit pops the top of the return stack into ip and advances
   it past the call to the just completed word.
*/
if (0) {
  op_exit:
    print_return_stack(rp0, rp);
    ip = *rp++;
    _debug("ip: %lx\n", (cell)ip);
    _next();
}
