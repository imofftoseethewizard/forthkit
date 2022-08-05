__primitive(pr_c_move)
{
    /* CMOVE ( addr1 addr2 u -- ) "c-move"

       Move u bytes beginning at address addr1 to addr2.  The byte
       at addr1 is moved first, proceeding toward high memory.  If
       u is zero nothing is moved.
     */
    register cell u = *sp++;
    register char *dest = (char *)_to_ptr(*sp++);
    register char *src = (char *)_to_ptr(*sp++);
    /* fprintf(stderr, "u: %d\n", u); */
    /* fprintf(stderr, "dest: %x (%lx)\n", _from_ptr(dest), dest); */
    /* fprintf(stderr, "src: %x (%lx)\n", _from_ptr(src), src); */
    for (; u != 0; u--) *dest++ = *src++;
}
__end
__define_primitive("cmove", pr_c_move);
