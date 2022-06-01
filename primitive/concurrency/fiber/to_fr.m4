__primitive(pr_to_fr)
{
    register cell *f = _to_fiber_ptr(*sp++);
    f[fa_rp] -= sizeof(cell);
    *_to_ptr(f[fa_rp]) = *sp++;
}
__end

__define_primitive(">fr", pr_to_fr);
