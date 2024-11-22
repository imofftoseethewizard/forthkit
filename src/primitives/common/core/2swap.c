pr_2swap:
{
    /* 2SWAP ( x1 x2 x3 x4 -- x3 x4 x1 x2 )

       Exchange the top two cell pairs.
     */

    _check_minimum_stack_depth(4);

    register cell tmp;

    tmp = *sp;
    *sp = *(sp+2);
    *(sp+2) = tmp;

    tmp = *(sp+1);
    *(sp+1) = *(sp+3);
    *(sp+3) = tmp;
}
