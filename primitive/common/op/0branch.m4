/* op_0branch expects that the word is an offset to the alternate code
   path, and immediately following that is the beginning of the
   consequent code path.
*/
__primitive(op_0branch)
{
    if (*sp++)
        /* skip over offset to alternate */
        ip++;
    else
        ip = (cell *)((char *)ip + (number)*ip);
}
__end

__define_primitive_ext("0branch:", op_0branch, c_operand_ip_offset);
