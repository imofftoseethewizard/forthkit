pr_rot:
{
    /* ROT ( n1 n2 n3 -- n2 n3 n1 ) "rote"

       Rotate the top three values, bringing the deepest to the top.
     */

    register cell tmp = *sp;
    *sp = *(sp+2), *(sp+2) = *(sp+1), *(sp+1) = tmp;
}
