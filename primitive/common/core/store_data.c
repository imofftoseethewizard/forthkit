primitive pr_store_data()
{
    /* , ( n -- ) "comma"

       Allot one cell in the dictionary, storing n there.
     */

    _store_data(*sp++);
    _check_dictionary_bounds();
}
