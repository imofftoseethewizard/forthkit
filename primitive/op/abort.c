/* Note that this abort is functionally distinct from the abort word.
 */
_primitive(op_abort) {
     reset_engine_execution_state(e);
     //TODO
//     goto __last;
}

register_operator(ot_abort, op_abort);
