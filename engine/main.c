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
  struct engine m;

  init_engine(&m);

  exit(run_engine(&m));
}
