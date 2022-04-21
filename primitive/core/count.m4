__primitive(pr_count)  
{

    register length_type *lenp = (length_type *)_to_ptr(*sp);

    *sp = _from_ptr(lenp + 1);
    *--sp = *lenp;

}
__end
__define_primitive("COUNT", pr_count);
