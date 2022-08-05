__primitive(pr_cell_plus)
{
    *sp += sizeof(cell);
}
__end
__define_primitive("cell+", pr_cell_plus);
