/*|

`2@ ( addr -- x1 x2 )`

Fetch the cell pair `x1` `x2` stored at `addr`. `x2` is stored at
`addr` and `x1` at the next consecutive cell. It is equivalent to the
sequence `DUP CELL+ @ SWAP @`.

  |*/

// 2@

pr_2fetch:
{
    register cell *p = _to_ptr(*sp);

    _check_minimum_stack_depth(1);

    *sp = *(p+1);
    *--sp = *p;
}
