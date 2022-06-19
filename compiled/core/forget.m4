
    /* FORGET ( -- )

       Used in the form:

       |   FORGET <name>

       If <name> is found in the compilation vocabulary, delete
       <name> from the dictionary and all words added to the
       dictionary after <name> regardless of their vocabulary.
       Failure to find <name> is an error condition.  An error
       condition also exists if the compilation vocabulary is
       deleted.

       |   : forget
       |       ' ?dup
       |       if
       |           dup 3 cells - @
       |           here - allot
       |           2 cells - @
       |           current @ !
       |       else
       |           -13 <abort>
       |       then
       |   ;
     */
    __compiled_word("FORGET", cw_forget, 0)

    _compile_cw(cw_tick);
    _compile_pr(pr_query_dup);

    _compile_if();

    _compile_pr(pr_dup);
    _compile_literal(3 * sizeof(cell));
    _compile_pr(pr_minus);
    _compile_pr(pr_fetch);

    _compile_pr(pr_here);
    _compile_pr(pr_minus);
    _compile_pr(pr_allot);

    _compile_literal(2 * sizeof(cell));
    _compile_pr(pr_minus);
    _compile_pr(pr_fetch);

    _compile_pr(pr_current);
    _compile_pr(pr_fetch);
    _compile_pr(pr_store);

    _compile_else();

    _compile_literal(-13);
    _compile_pr(op_abort);

    _compile_then();

    _compile_pr(op_exit);
