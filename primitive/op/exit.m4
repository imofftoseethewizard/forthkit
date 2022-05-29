#define _exit() ip = *rp ? _to_ptr(*rp) : 0, rp++

/* op_exit pops the top of the return stack into ip and advances
   it past the call to the just completed word.
*/

__primitive(op_exit)
{
    _exit();
    _check_return_stack_bounds();
}
__end
__define_primitive("EXIT", op_exit);
