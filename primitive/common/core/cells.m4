__primitive(pr_cells)
{
    *sp = *sp * sizeof(cell);
}
__end
__define_primitive("CELLS", pr_cells);
