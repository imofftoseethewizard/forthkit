primitive pr_query_dup()
{
    /* ?DUP ( n -- n [ n ] ) "query-dupe"

     Duplicate n if it is non-zero.
     */
    register cell n = *sp;

    if (n) *--sp = n;
}
