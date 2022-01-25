register_operator(ot_jump, &&op_jump);

/* op_jump expects the next location to be an offset. It is relative
   to where the ip would normally be next, hence the `+ 2` to account
   for advancing past op_jump and the offset.
*/

if (0) {
  op_jump:
     ip += (long int)*++ip;
     _next();
}

/* _compile_jump_origin is used to build control structures. It compiles a forward
   jump with a zero offset and saves the address of the offset on the stack.
   Later, when the compiler reaches the destination of the jump, the address is
   taken from the stack to complete its compilation.
*/
#define _compile_jump_origin() *here++ = (cell)&&op_jump, *--sp == (cell)here, *here++ = 0

/* _compile_jump_target
 */
#define _compile_jump_target() *(cell *)*sp++ = (cell)(here + 1 - (cell *)*sp)
