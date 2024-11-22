/*|

`XOR ( w1 w2 -- w3 )`

`w3` is the bit-by-bit exclusive-or of `w1` with `w2`.

  |*/

// XOR

pr_xor:
{
    *++sp = *(sp+1) ^ *sp;
}
