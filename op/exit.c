register_operator(ot_exit, &&op_exit);

/* op_exit pops the top of the return stack into ip and advances
   it past the call to the just completed word.
*/
if (0) {
  op_exit:
     ip = (void **)*rp++;
     _next();
}
