/* op_branch expects that the next two words are op_jump and an offset
   to the alternate code path, and immediately following that is
   the beginning of the consequent code path.
*/
__primitive(op_branch)
{
    ip += *sp++ ? 2 : 0;
}
__end

__define_primitive("<branch>", op_branch);
