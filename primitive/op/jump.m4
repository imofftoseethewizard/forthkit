/* _compile_jump_origin is used to build control structures. It compiles a forward
   jump with a zero offset and saves the address of the offset on the stack.
   Later, when the compiler reaches the destination of the jump, the address is
   taken from the stack to complete its compilation.
*/
#define _compile_jump_origin() \
    _compile_pr(op_jump), *--sp = _from_ptr(here), _store_data(0)

/* _compile_jump_target
 */

#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#define _compile_jump_target() \
    *_to_ptr(*sp++) = (int)(here + sizeof(cell) - (char *)_to_ptr(*sp))

/* op_jump expects the next location to be an offset. It is relative
   to where the ip would normally be next, hence the "+ 2" to account
   for advancing past op_jump and the offset.
*/

__primitive(op_jump)  
{
    _debug("jump: *ip: %lx, %ld\n", (long)*ip, (long)*ip);
    ip = (cell *)((char *)ip + (number)*ip - sizeof(cell));
    _debug("jump: *ip: %lx\n", (long)*ip);
}
__end