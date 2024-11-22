/*|

`ALLOT ( n -- )`

Allocates n bytes in the dictionary. The address of the next available
dictionary entry is updated accordingly.

  |*/

// ALLOT

pr_allot:
{
    dp += (number)*sp++;
    _check_dictionary_bounds();
}
