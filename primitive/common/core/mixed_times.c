primitive pr_m_times()
{
    double_number d = *(number *)sp * *(number *)(sp+1);

    *(sp+1) = _from_high_word(d);
    *sp = _from_low_word(d);
}
