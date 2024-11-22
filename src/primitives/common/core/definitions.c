/*|

`DEFINITIONS ( -- )`

The compilation vocabulary is changed to be the same as the first
vocabulary in the search order.

  |*/

// DEFINITIONS

pr_definitions:
{
	// TODO concurrency
    tp[ta_current] = tp[ta_context];
}
