primitive pr_do_does()
{
    register cell *word = _to_ptr(*_to_ptr(tp[ta_current]));
    register cell *origp = _get_word_interpretation_ptr(word);

    *origp = (cell)_from_pr(op_does);
    *(origp + 1) = *sp++;

}
