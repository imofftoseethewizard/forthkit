if (!e[ea_interpret]) {
     /*
       The following is a minimal text interpreter using word and find.
       It doesn't have any error reporting, and it only understands words
       in the dictionary and unsigned integer literals.

       : interpret
           begin
               \ Read the next space-delimited word from the input stream.
               32 word ?dup
               ( 0 | c-addr c-addr )

           while

               \ Look up the word in the current context. If found, return
               \ its xt and 1 if the word is immediate, -1 otherwise. If the
               \ word is not found, leave the c-addr and push 0.

               dup find ?dup
               ( c-addr 0 | c-addr xt xt )
               if
                   ( c-addr xt )

                   swap drop

                   \ Check state and the immediate flag, executing or compiling
                   \ as appropriate. The flags of the word is in the cell immediately
                   \ before the compilation address, and the immediate flag is
                   \ in the lsb.

                   dup <cell> - @ 1 and state @ 0= or
                   if execute else compile, then

               else
                   \ The word was not found in the current context. Attempt to
                   \ interpret it as a literal.

                   ( c-addr )
                   0 over count >number
                   ( c-addr ud c-addr2 u )

                   \ If u is 0, then the entirety of the word was consumed in converting
                   \ it to a number, and that will be in ud.

                   0= if

                       \ c-addr and c-addr2 aren't needed anymore, so drop, swap, and drop
                       \ clear them out. If we're compiling, then compile a literal,
                       \ else just leave the value on the stack.

                       drop swap drop state @ if literal then
                   else

                       \ <abort> refers to the internal operator for abort, which is much like
                       \ throw in later FORTH versions. -13 is the throw code for an
                       \ unrecognized word. See https://forth-standard.org/standard/exception

                       -13 <abort>
                   then
               then
           repeat
       ;

       It's compiled line by line below.
     */

    /* : interpret                                       */
    _begin_define_word("interpret", 0);

    e[ea_interpret] = _from_ptr(here);

    _info("defining interpret        %lx\n", (long)e[ea_interpret]);

    /*      begin                                        */
    _compile_begin();

    /*          32 word ?dup                             */
    _compile_pr(op_literal);
    _store_data(32);
    _compile_pr(pr_word);
    _compile_pr(pr_q_dup);

    /*      while                                        */
    _compile_while();

    /*          dup find ?dup                            */
    _compile_pr(pr_dup);
    _compile_pr(pr_find);
    _compile_pr(pr_q_dup);

    /*          if                                       */
    _compile_if();

    /*              swap drop                            */
    _compile_pr(pr_swap);
    _compile_pr(pr_drop);

    /*              dup <cell> - @ 1 and state @ 0= or   */
    /*              0> state @ 0= or                     */
    _compile_pr(pr_dup);
    _compile_pr(op_literal);
    _store_data(sizeof(cell));
    _compile_pr(pr_minus);
    _compile_pr(pr_fetch);
    _compile_pr(op_literal);
    _store_data(1);
    _compile_pr(pr_and);
    _compile_pr(pr_state);
    _compile_pr(pr_fetch);
    _compile_pr(pr_zero_eq);
    _compile_pr(pr_or);

    /*              if execute else compile, then        */
    _compile_if();
    _compile_pr(pr_execute);
    _compile_else();
    _compile_pr(pr_store_compiled);
    _compile_then();

    /*          else                                     */
    _compile_else();

    /*              0 over count >number                 */
    _compile_pr(op_literal);
    _store_data(0);
    _compile_pr(pr_over);
    _compile_pr(pr_count);
    _compile_pr(pr_to_number);

    /*              0= if                                */
    _compile_pr(pr_zero_eq);
    _compile_if();

    /*                  drop swap drop state @ if literal then */
    _compile_pr(pr_drop);
    _compile_pr(pr_swap);
    _compile_pr(pr_drop);
    _compile_pr(pr_state);
    _compile_pr(pr_fetch);
    _compile_if();
    _compile_pr(pr_literal);
    _compile_then();

    /*              else                                 */
    _compile_else();

    /*                   -13 <abort>                     */
    _compile_pr(op_literal);
    _store_data(-13);
    _compile_pr(op_abort);

    /*              then                                 */
    _compile_then();

    /*          then                                     */
    _compile_then();

    /*      repeat                                       */
    _compile_repeat();

    /*  ;                                                */
    _compile_pr(op_exit);

    sp = sp0;
    rp = rp0;
    ip = 0;
    _debug("done defining interpret\n");
}

/*
  Alternate version, with modern words parse-name, find-name, etc.
  begin
  parse-name ( c-addr n ) ?dup
  while
  find-name
  ?dup-if
  state if name>compile else name>interpret then execute
  else
  parse-literal
  then
  repeat
  drop
*/
