__primitive(pr_colon)  
{

    tp[ta_context] = tp[ta_current];
    e[ea_state] = 1;

    _store_word_name();
    _word_header(0);

}
__end
__define_parsing_primitive(":", pr_colon);
