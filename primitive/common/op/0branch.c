/* op_0branch expects that the word is an offset to the alternate code
   path, and immediately following that is the beginning of the
   consequent code path.
*/
primitive op_0branch()
{
    if (*sp++)
        /* skip over offset to alternate */
        ip++;
    else
        ip = (cell *)((char *)ip + (number)*ip);
}
