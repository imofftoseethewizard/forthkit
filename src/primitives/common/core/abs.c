/*|

`ABS ( n -- u )`

u is the absolute value of n. Note that u is unsigned, and that abs
has two fixed points. The first is obviously zero since -0 = 0. The
second is the most negative integer representable by the cell
size. Call this number M. M will have a 1 in the most significant bit
and all the lower bits will be 0. This is coincidentally the
representation of the absolute value of M as an unsigned integer. For
example, using a 4 bit word, M would be b1000 (-8) and abs(M) = 8,
which is also b1000.

  |*/

// ABS

pr_abs:
{
    if ((number)*sp < 0) *sp = -(number)*sp;
}
