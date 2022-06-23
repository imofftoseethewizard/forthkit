__primitive(pr_less_sharp)
{
    /* <# ( -- ) "less-sharp"

       Initialize pictured numeric output conversion.  The words:
       #  #>  #S  <#  HOLD and SIGN can be used to specify the
       conversion of a double number into an ASCII text string stored
       in right-to-left order.
     */

    *_number_pad_idx_addr() = _c_number_pad_size;
}
__end
__define_primitive(`"<#"', pr_less_sharp);
