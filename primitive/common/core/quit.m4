__primitive(pr_quit)
{
    /* QUIT ( -- )

       Clears the return stack, sets interpret state, and ends
       evaluation of the current input source. No message is
       displayed.
     */

    rp = rp0;
    ip = 0;
    tp[ta_state] = 0;
}
__end
__define_primitive("quit", pr_quit);
