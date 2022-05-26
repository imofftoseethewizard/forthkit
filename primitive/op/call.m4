/* currently unused, has problems when the cell size < machine word size */

/* op_call expects the next location to be a pointer to a native
   function that neither accepts arguments nor returns a value.
*/
__primitive(op_call)
{
    ((native_word)*ip++)();
}
__end

__define_primitive("call", op_call, c_operand_ip); /* nb: c_operand_ip is not defined */
