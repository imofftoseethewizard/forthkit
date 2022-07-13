
__primitive(pr_end_convert_number)
{
    /* #> ( ud -- addr u )

       Pictured numeric output conversion is ended dropping ud.
       addr is the address of the resulting output string. u is
       the number of characters in the output string. addr and u
       together are suitable for TYPE .
     */

    register unsigned char *idx = _number_pad_idx_addr();
    register char *chp = _number_pad_buf_addr();
    *(sp+1) = _from_ptr(chp + *idx);
    *sp = _c_number_pad_size - *idx;
}
__end
__define_primitive(`"#>"', pr_end_convert_number);
