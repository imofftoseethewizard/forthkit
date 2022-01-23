/*
 *
 * main.c
 *
 * This module is responsible for argument parsing and initializing the spire engine.
 */

#include <stdlib.h>
#include "machine.h"

int
main(int argc, char *argv[])
{
  struct stack_machine m;

  init_stack_machine(&m);

  exit(run_stack_machine(&m));
}
