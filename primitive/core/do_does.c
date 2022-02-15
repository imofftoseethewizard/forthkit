_primitive(pr_do_does) {
    register cell *word = _to_ptr(e[e[ea_current]]);
    register cell *origp = _get_word_interpretation_ptr(word);
    register cell *doesp = (cell *)here;

    _store_data(*origp);
    _store_data(*(origp+1));

    _debug("origp: %lx %x\n", (long)origp, _from_ptr(origp));
    *origp = (cell)_pr_addr(op_jump);
    *(origp+1) = (doesp - origp + 1) * sizeof(cell);
}
