pr_leave:
{
    /* LEAVE ( -- ) compiling: ( -- )

       Transfers execution to just beyond the next LOOP or +LOOP .
       The loop is terminated and loop control parameters are
       discarded.  May only be used in the form:

       |   DO ... LEAVE ... LOOP

       or

       |   DO ... LEAVE ... +LOOP

       LEAVE may appear within other control structures which are
       nested within the do-loop structure.  More than one LEAVE
       may appear within a do-loop.

       Use of this leave implementation requires the use of
       compatible DO and LOOP or +LOOP primitves. During
       compilation LEAVE expects the top of the stack to hold the
       address of the most recent leave's jump operand. It stores
       that value where at its jump operand should go and replaces
       it with the value for itself, thus forming a linked
       list. The loop-ending word will traverse the list and fill
       in the appropriate offsets, ending when it comes to the
       address of the start of the loop.
     */

    _compile_pr(pr_unloop);
    _compile_pr(op_jump);
    _store_data(leave_link);
    leave_link = _from_ptr(dp - sizeof(cell));
}
