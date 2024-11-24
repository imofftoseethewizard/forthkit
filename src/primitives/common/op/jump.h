/* _compile_jump_origin is used to build control structures. It compiles a forward
   jump with a zero offset and saves the address of the offset on the stack.
   Later, when the compiler reaches the destination of the jump, the address is
   taken from the stack to complete its compilation.
*/
#define _compile_jump_origin() \
    _compile_pw(op_jump), *--sp = _from_ptr(dp), _store_data(0)

/* _compile_jump_target
 */

#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#define _compile_jump_target() \
    *_to_ptr(*sp++) = (int)(dp - (char *)_to_ptr(*sp))

/* op_jump expects the next location to be an offset. It is relative
   to the cell where the offset is stored.
 */

#define _jump() (ip = (cell *)((char *)ip + (number)*ip))
