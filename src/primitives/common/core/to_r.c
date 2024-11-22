/*|

`>R ( n -- )`

Transfer `n` to the return stack.  Every `>R` must be balanced by a `R>` in
the same control structure nesting level of a colon-definition.

  |*/

// >R

pr_to_r:
{
    *--rp = *sp++;
    _check_return_stack_bounds();
}
