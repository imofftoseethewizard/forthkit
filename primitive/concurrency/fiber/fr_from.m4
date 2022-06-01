__primitive(pr_fr_from)
{
    register cell *f = _to_fiber_ptr(*sp);
    *sp = *_to_ptr(f[fa_rp]);
    f[fa_rp] += sizeof(cell);
}
__end

__define_primitive("fr>", pr_fr_from);
