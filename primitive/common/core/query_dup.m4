__primitive(pr_query_dup)
{
    /* ?DUP ( n -- n [ n ] ) "query-dupe"

     Duplicate n if it is non-zero.
     */
    if (*sp) *--sp = *(sp+1);
}
__end
__define_primitive("?DUP", pr_query_dup);
