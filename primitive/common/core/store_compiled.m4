__primitive(pr_store_compiled)
{
    register cell xt = *sp;

    if (_is_primitive(xt))
        _store_data(xt);

    else {
        register cell *code = _to_ptr(xt);
        register cell flags = *(code - 1);

        if (flags & c_inline_mask) {

            if (flags & c_inline1)
              _store_data(*code);

            else if (flags & c_inline2) {

                _store_data(*code);
                _store_data(*(code + 1));

            } else {

                _store_data(*code);
                _store_data(*(code + 1));
                _store_data(*(code + 2));

            }

        } else
            _store_data(xt);
    }

    sp++;

    _check_dictionary_bounds();
}
__end
__define_primitive(`"COMPILE,"', pr_store_compiled);
