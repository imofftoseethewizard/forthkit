__primitive(pr_c_move_up)
{
    /* CMOVE> ( addr1 addr2 u -- ) "c-move-up"

       Move the u bytes at address addr1 to addr2.  The move begins
       by moving the byte at (addr1 plus u minus 1) to (addr2 plus
       u minus 1) and proceeds to successively lower addresses for
       u bytes.  If u is zero nothing is moved.  (Useful for
       sliding a string towards higher addresses).
     */

    register cell u = *sp++;
    register char *dest = (char *)_to_ptr(*sp++) + u - 1;
    register char *src = (char *)_to_ptr(*sp++) + u - 1;
    for (; u != 0; u--) *dest-- = *src--;
}
__end
__define_primitive("CMOVE>", pr_c_move_up);
