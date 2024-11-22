/*|

`+! ( n addr -- )`

Add `n` to the value at `addr`.

  |*/

// +!

pr_plus_store:
{
	*_to_ptr(*sp) += *(sp+1), sp += 2;
}
