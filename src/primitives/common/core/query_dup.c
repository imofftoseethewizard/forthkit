/*|

`?DUP ( n -- n [ n ] )`

Duplicate `n` if it is non-zero.
  |*/

// ?DUP

pr_query_dup:
{
    register cell n = *sp;

    if (n) *--sp = n;
}
