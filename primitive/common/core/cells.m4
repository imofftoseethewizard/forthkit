__primitive(pr_cells)
{
    *sp = *sp * sizeof(cell);
}
__end
__define_primitive("cells", pr_cells);
