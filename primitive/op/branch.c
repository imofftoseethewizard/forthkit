/* op_branch expects that the next two words are op_jump and an offset
   to the alternate code path, and immediately following that is
   the beginning of the consequent code path.
*/
_primitive(op_branch) {
    _debug("branch: ");
    _print_stack();
    ip += *sp++ ? 2 : 0;
    _next();
}

register_operator(ot_branch, op_branch);
