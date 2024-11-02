pr_leave:
{
    /* LEAVE ( -- )

       Force termination of a DO-LOOP at the next LOOP or +LOOP by
       setting the loop limit equal to the current value of the
       index. The index itself remains unchanged, and execution
       proceeds normally until the loop terminating word is
       encountered.
     */

    *(rp+1) = *rp;
}
