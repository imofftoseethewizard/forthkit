__primitive(pr_times_div)  
{
    register double_number
      q = _to_low_word((number)*sp++),
      p = _to_low_word((number)*sp++) * _to_low_word((number)*sp++);

    *--sp = _from_low_word(p/q);
}
__end
__define_primitive("*/", pr_times_div);
