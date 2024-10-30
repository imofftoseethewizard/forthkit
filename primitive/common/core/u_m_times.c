primitive pr_u_m_times()
{
    /* UM* ( u1 u2 -- ud ) "u-m-times"

       ud is the unsigned product of u1 times u2.  All values and
       arithmetic are unsigned.
     */

    register cell
      u2 = *sp++,
      u1 = *sp++;

    register double_number ud = _to_low_word(u1) * _to_low_word(u2);

    *--sp = _from_low_word(ud);
    *--sp = _from_high_word(ud);
}
