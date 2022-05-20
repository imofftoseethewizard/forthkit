#define _compile_literal(x) do { _compile_pr(op_literal); _store_data(x); } while (0)

__primitive(op_literal)
{
    *--sp = (cell)*ip++;
}
__end

__define_operator("literal", op_literal);
