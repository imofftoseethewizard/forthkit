__primitive(pr_hold_digit)
{
    /* # ( ud1 -- ud2 )

       The remainder of ud1 divided by the value of BASE is
       converted to an ASCII character and appended to the output
       string toward lower memory addresses. ud2 is the quotient
       and is maintained for further processing. Typically used
       between <# and #> .

       Implemented in Forth would look something like this

           base @ >r decimal

           : # ( ud1 -- ud2 )

               base @ s>d
               ud/mod rot
               10 < if 48 else 55 then +
               hold
           ;

           r> base !

       where ud/mod ( ud u -- urem udquot ) is defined by Gforth.

       possible modules: core text io
     */

    register double_cell n = _to_high_word(*sp++) | _to_low_word(*sp++);
    register cell digit = (cell)(n % tp[ta_base]);

    _hold(digit + (digit <= 9 ? '0' : 'a' - 10));
    n /= tp[ta_base];

    *--sp = _from_low_word(n);
    *--sp = _from_high_word(n);
}
__end
__define_primitive(`"#"', pr_hold_digit);
