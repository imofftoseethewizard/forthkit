__primitive(pr_f_at)
{
    register cell n = *sp;

    if (fp >= fp0 - n)
        _abort(err_fiber_stack_underflow);

    else
        *sp = *(fp + n);
}
__end

__define_primitive(`"f@"', pr_f_at);
