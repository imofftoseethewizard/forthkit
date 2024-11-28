/*|

`FORTH ( -- )`

The name of the primary vocabulary. Execution replaces the first
vocabulary in the search order with `FORTH`.  `FORTH` is initially the
compilation vocabulary and the first vocabulary in the search order.
New definitions become part of the `FORTH` vocabulary until a
different compilation vocabulary is established.

  |*/

// FORTH

pr_forth:
{
    _set_context(_from_ptr(&_forth()));
}
