#define _allot() dp += (number)*sp++

__primitive(pr_allot)  
{
    _allot();
}
__end
__define_primitive("ALLOT", pr_allot);
