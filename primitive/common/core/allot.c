pr_allot:
{
    /* ALLOT ( n -- )

       Allocates n bytes in the dictionary. The address of the
       next available dictionary entry is updated accordingly.
     */

    dp += (number)*sp++;
    _check_dictionary_bounds();
}