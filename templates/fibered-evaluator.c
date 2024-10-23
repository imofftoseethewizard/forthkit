int
evaluate(evaluator *x, const char *source)
{
    /** declare evaluator variables **/
    /** declare primitives **/

    int result = 0;

    register cell *m = x->memory;

    register byte *dp;
    register byte *top;

    register cell *fp0;
    register cell *fp;
    register cell *ip;
    register cell *rp0;
    register cell *rp;
    register cell *rp_stop;
    register cell *sp0;
    register cell *sp;
    register cell *tp;

    register number steps;

    /** conditionally include bootstrap **/

    _debug("interpreting source '%s'\n", source);

    /* copy source into evaluator memory */
    m[ea_source_idx] = 0;
    m[ea_source_len] = strlen(source);
    memcpy(_to_ptr(m[ea_source_addr]), source, m[ea_source_len]);

    /* set values of local variables */
    _load_evaluator_state();

    /* push new fiber for the interpreter task onto fiber stack */
    fp = fp0 = _to_ptr(m[ea_fp0]);
    *--fp = _primary_fiber;

    /* set up stack, ip for to call interpreter */
    rp = rp_stop = rp0;
    *--rp = 0;
    ip = _to_ptr(m[ea_interpret]);
    steps = -1;

    /* synchronize local variables and memory */
    _save_evaluator_state();

    /** implement evaluator core **/

    _debug("result: %d\n", result);
    _print_stack();

    return result;
}
