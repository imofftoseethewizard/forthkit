/*|

### `<abort>` ( n -- <empty> )

Sets evaluator result to `n`.  Clear the data and return stacks,
setting execution mode.  End evaulation of current input source.

  |*/

// <abort>
op_abort:
{

    _abort(*sp);
}
