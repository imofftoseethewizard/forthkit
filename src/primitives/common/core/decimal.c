/*|

`DECIMAL ( -- )`

Set the input-output numeric conversion base to ten.

  |*/

// DECIMAL

pr_decimal:
{
	// TODO concurrency

    tp[ta_base] = 10;
}
