pr_to_in:
{
    /* >IN ( -- addr ) "to-in"

       The address of a variable which contains the present
       character offset within the input stream {{0..the number of
       characters in the input stream}}.
     */

    *--sp = _from_ptr(&e[ea_source_idx]);
}
