__primitive(pr_num_f)
{
    *--sp = fp0 - fp;
}
__end

__define_primitive(`"#f"', pr_num_f);
