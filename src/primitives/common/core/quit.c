/*|

`QUIT ( -- )`

Clears the return stack, sets interpret state, and ends evaluation of
the current input source. No message is displayed.

  |*/

// QUIT

pr_quit:
{
    rp = rp0;
    ip = 0;
    _set_state(0);
}
