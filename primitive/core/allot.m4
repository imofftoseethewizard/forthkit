#define _allot() dp += (number)*sp++

__primitive(pr_allot)
{
    _allot();
    _check_dictionary_bounds();
}
__end
__define_primitive("ALLOT", pr_allot);
