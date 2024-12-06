/*|

### `EXECUTE` ( addr -- )

Execute the dictionary entry whose compilation address is on the
stack.

  |*/

// EXECUTE

pr_execute:
{
    wp = *sp++;
    goto *(cell *)_to_pv(*wp++);
}
