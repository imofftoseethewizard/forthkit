/* ! ( n addr -- ) "store"

   Store n at addr.
 */
#define _store() *_to_ptr(*sp) = *(sp+1), sp += 2

__primitive(pr_store)
{
    /* ! ( n addr -- ) "store"

       Store n at addr.
     */
    _store();
}
__end
__define_primitive("!", pr_store);
