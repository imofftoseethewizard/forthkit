/*|

### `EXECUTE` ( addr -- )

Execute the dictionary entry whose compilation address is on the
stack.

  |*/

// EXECUTE

pr_execute:
{
    wp = _to_ptr(*sp++);

    _check_parameter_stack_bounds();
    _print_stack();

    continue;
}
