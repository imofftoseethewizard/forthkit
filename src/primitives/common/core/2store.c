/*|

`2! ( x1 x2 addr -- )`

Store the cell pair `x1` `x2` at addr, with `x2` at `addr` and `x1` at
the next consecutive cell. It is equivalent to the sequence `SWAP OVER
!  CELL+ !`.

  |*/

// 2!

pr_2store:
{
    *_to_ptr(*sp) = *(sp+1);
    *(_to_ptr(*sp)+1) = *(sp+2);
    sp += 3;
}
