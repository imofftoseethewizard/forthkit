/* +! ( n addr -- ) "plus-store"

   Add n to the value at addr.

 */
#define _plus_store() *_to_ptr(*sp) += *(sp+1), sp += 2

__primitive(pr_plus_store)
{
    /* +! ( n addr -- ) "plus-store"

       Add n to the value at addr.

     */
    _plus_store();
}
__end
__define_primitive("+!", pr_plus_store);
