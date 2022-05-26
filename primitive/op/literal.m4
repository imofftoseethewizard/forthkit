#define _compile_literal(x) do { _compile_pr(op_literal); _store_data(x); } while (0)

__primitive(op_literal)
{
    *--sp = (cell)*ip++;
}
__end

__define_primitive_ext("<literal>", op_literal, c_operand_literal);
