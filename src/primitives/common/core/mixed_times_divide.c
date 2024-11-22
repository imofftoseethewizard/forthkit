pr_mixed_times_divide:
{
    register number
      n2 = *sp++,
      n1 = *sp++,
      u1 = n1 < 0 ? -n1 : n1;

    register double_number d1 = _to_high_word(*sp++) | _to_low_word(*sp++);
    register double_cell
      ud1 = d1 < 0 ? -d1 : d1,
      uh1 = (double_cell)_from_high_word(ud1) * u1,
      ul1 = (double_cell)_from_low_word(ud1) * u1,
      uq_h = uh1 / n2,
      uq_l = (ul1 + _to_high_word(_from_low_word(uh1 % n2))) / n2,
      uq = _to_high_word(_from_low_word(uq_h)) + uq_l,
      q = ((n1 & c_msb) ^ (_from_high_word(d1) & c_msb)) ? -uq : uq;

    *--sp = _from_low_word(q);
    *--sp = _from_high_word(q);
}
