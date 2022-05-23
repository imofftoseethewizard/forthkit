#define _digit(x) ((x) <= 9 ? '0' + (x) : 'a' + (x) - 10)

__primitive(pr_num)  
{
    register double_cell n = _to_high_word(*sp++) | _to_low_word(*sp++);

    _hold(_digit(n % tp[ta_base]));
    n /= tp[ta_base];

    *--sp = _from_low_word(n);
    *--sp = _from_high_word(n);

}
__end
__define_primitive(`"#"', pr_num);
