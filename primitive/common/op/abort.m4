#define _abort(x) result = (x), sp = sp0, rp = rp0, ip = 0, tp[ta_state] = 0

__primitive(op_abort)
{
    /* ABORT ( n -- <empty> )

       Sets evaluator result to n. Clear the data and return
       stacks, setting execution mode. End evaulation of current
       input source.
     */

    _abort(*ip);
}
__end
__define_primitive("abort:", op_abort);
