pr_xor:
{
    /* XOR ( w1 w2 -- w3 ) "x-or"

       w3 is the bit-by-bit exclusive-or of w1 with w2.
     */

    *++sp = *(sp+1) ^ *sp;
}
