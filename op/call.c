register_operator(ot_call, &&op_call);

/* op_call expects the next location to be a pointer to a native
   function that neither accepts arguments nor returns a value.
*/
if (0) {
  op_call:
     ((native_word)*++ip)();
     next();
}
