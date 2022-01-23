/*
 *
 * main.c
 *
 * This module is responsible for argument parsing and initializing the spire engine.
 */

#include <stdlib.h>
#include <assert.h>

#include "machine.h"

int
main(int argc, char *argv[])
{
  struct stack_machine m;
  int result;

  init_stack_machine(&m);

  /* Set up dictionary. */
  result = run_stack_machine(&m);
  assert(result == 0);

  test_op_abort(&m);
}
