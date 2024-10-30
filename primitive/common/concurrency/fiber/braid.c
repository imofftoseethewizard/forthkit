primitive pr_braid()
{
    register cell f_tmp;
    register cell n = *sp++;

    if (fp >= fp0 - n)
        _abort(err_fiber_stack_underflow);

    else if (fp < fp0 - 1) {

        if (n == 0)
            _save_fiber_state();

        f_tmp = *(fp+1);
        *(fp+1) = *(fp+n);
        *(fp+n) = f_tmp;

        if (n == 0)
            _load_fiber_state();
    }
}
