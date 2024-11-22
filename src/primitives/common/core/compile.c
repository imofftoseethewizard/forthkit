/*|

`COMPILE ( -- )`

Typically used in the form:

    : <name> ... COMPILE <namex> ... ;

When <name> is executed, the compilation address compiled for <namex>
is compiled and not executed.  <name> is typically immediate and
<namex> is typically not immediate.

  |*/

// COMPILE

pr_compile:
{
    *(cell *)dp = *ip++;
    _check_dictionary_bounds();
}
