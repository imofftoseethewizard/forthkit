pr_to_body:
{
    /* >BODY ( addr1 -- addr2 ) "to-body"

       addr2 is the parameter field address corresponding to the
       compilation address addr1.
    */

    /* CREATE compiles op literal, an address, and op exit. The cell
       immediately after that is the start of the parameter field for
       the CREATEd word, hence the following:
     */
    *sp += 3 * sizeof(cell);
}
