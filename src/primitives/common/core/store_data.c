/*|

`, ( n -- )`

Allot one cell in the dictionary, storing `n` there.

  |*/

// ,

pr_store_data:
{
    _store_data(*sp++);
    _check_dictionary_bounds();
}
