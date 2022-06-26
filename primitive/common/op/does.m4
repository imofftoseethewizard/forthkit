__primitive(op_does)
{
    /* Note ip points to the cell after op_does. That cell contains
       the address of the code following does>. After that is the
       first cell of the parameter field for the word defined by the
       word containing does>.
     */
    *--sp = _from_ptr(ip + 2); /* skip over does> code addr, op_exit */
    ip = _to_ptr(*ip);
}
__end

__define_primitive_ext("<does>", op_does, c_operand_ip_offset);
