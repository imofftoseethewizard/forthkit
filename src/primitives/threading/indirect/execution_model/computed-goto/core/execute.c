/*|

### `EXECUTE` ( addr -- )

Execute the dictionary entry whose compilation address is on the
stack.

  |*/

// EXECUTE

pr_execute:
{
    wp = _to_ptr(*sp++);
    goto *(cell *)_to_pv(*wp++);
}
