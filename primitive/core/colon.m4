__primitive(pr_colon)  
{

    e[ea_context] = e[ea_current];
    e[ea_state] = 1;

    _store_word_name();
    _word_header(0);

}
__end
__define_parsing_primitive(":", pr_colon);