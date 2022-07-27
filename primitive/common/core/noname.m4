__primitive(pr_noname)
{
    _word_header(0);
    *(sp-1) = *sp;
    *sp = tp[ta_latest_xt];
    sp--;
}
__end
__define_primitive(":NONAME", pr_noname);
