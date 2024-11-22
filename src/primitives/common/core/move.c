// MOVE

pr_move:
{
    register number n = *sp++;
    register cell *dest = _to_ptr(*sp++);
    register cell *src = _to_ptr(*sp++);
    for (; n > 0; n--) *dest++ = *src++;
}
