/*|

`! ( n addr -- )`

Store `n` at `addr`.

  |*/

// !

pr_store:
{
    *_to_ptr(*sp) = *(sp+1);
    sp += 2;
}
