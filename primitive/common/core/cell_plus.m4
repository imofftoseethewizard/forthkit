__primitive(pr_cell_plus)
{
    *sp += sizeof(cell);
}
__end
__define_primitive("CELL_PLUS", pr_cell_plus);
