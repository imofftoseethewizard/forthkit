pr_f_at:
{
    register cell n = *sp;

    if (fp >= fp0 - n)
        _abort(err_fiber_stack_underflow);

    else
        *sp = *(fp + n);
}
