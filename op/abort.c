register_operator(op_type_abort, &&op_abort);

if (0)
  {
  op_abort:
    reset_stack_machine_execution_state(m);
    goto __last;
  }
