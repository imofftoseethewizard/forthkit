/* +! ( n addr -- ) "plus-store"

   Add n to the value at addr.

 */
#define _plus_store() *_to_ptr(*sp) += *(sp+1), sp += 2
