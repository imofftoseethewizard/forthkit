register_operator(ot_abort, op_abort);

/* Note that this abort is functionally distinct from the abort word.
 */
_primitive(op_abort) {
     reset_engine_execution_state(e);
     goto __last;
}
None