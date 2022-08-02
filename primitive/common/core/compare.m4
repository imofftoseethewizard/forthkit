__primitive(pr_compare)
{
    register char *s1, *s2;
    register cell c1, c2;
    register int r;

    c2 = *sp++;
    s2 = (char *)_to_ptr(*sp++);
    c1 = *sp++;
    s1 = (char *)_to_ptr(*sp++);

    r = strncmp(s1, s2, c1 <= c2 ? c1 : c2);
    if (r)
        *--sp = (cell)r;
    else
        *--sp = (cell)(((c1 - c2) > 0) - ((c1 - c2) < 0));
}
__end
__define_primitive("COMPARE", pr_compare);
