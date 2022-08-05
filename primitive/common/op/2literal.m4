__primitive(op_2literal)
{
    *--sp = (cell)*(ip+1);
    *--sp = (cell)*ip;
    ip += 2;
}
__end

__define_primitive_ext("2lit:", op_2literal, c_operand_literal);
