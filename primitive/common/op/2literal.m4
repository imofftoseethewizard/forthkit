#define _compile_2literal(x, y) do { _compile_pr(op_2literal); _store_data(x); _store_data(y); } while (0)

__primitive(op_2literal)
{
    *--sp = (cell)*ip++;
    *--sp = (cell)*ip++;
}
__end

__define_primitive_ext("<2literal>", op_2literal, c_operand_2literal);
