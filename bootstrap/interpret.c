if (!interpret) {
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

               find ?dup
               ( c-addr 0 | xt 1 1 | xt -1 =1 )
               if
                   ( xt 1 | xt -1 )

                   \ Check state and the immediate flag, executing or compiling
                   \ as appropriate.

                   0> state @ 0= or
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

                       \ c-addr and c-addr2 aren't needed anymore, so drop and nip
                       \ clear them out. If we're compiling, then compile a literal,
                       \ else just leave the value on the stack.

                       drop nip state @ if literal then
                   else

                       \ This doesn't provide much in the way of error feedback,
                       \ but this is also just the bootstrap interpreter. The caller
                       \ can check source_idx against source_len.

                       abort
                   then
               then
           repeat
       ;

       It's compiled line by line below.
     */

    /* : interpret                                       */
    begin_define_word("interpret", 0);
    interpret = (void *)here;
    _debug("defining interpret        (%lx)\n", (cell)interpret);

    /*      begin                                        */
    _compile_begin();

    /*          32 word ?dup                             */
    _store_data(&&op_literal);
    _store_data(32);
    _store_data(&&pr_word);
    _store_data(&&pr_q_dup);

    /*      while                                        */
    _compile_while();

    /*          find ?dup                                */
    _store_data(&&pr_find);
    _store_data(&&pr_q_dup);

    /*          if                                       */
    _compile_if();

    /*              0> state @ 0= or                     */
    _store_data(&&pr_zero_gt);
    _store_data(&&pr_state);
    _store_data(&&pr_fetch);
    _store_data(&&pr_zero_eq);
    _store_data(&&pr_or);

    /*              if execute else compile, then        */
    _compile_if();
    _store_data(&&pr_execute);
    _compile_else();
    _store_data(&&pr_store_compiled);
    _compile_then();

    /*          else                                     */
    _compile_else();

    /*              0 over count >number                 */
    _store_data(&&op_literal);
    _store_data(0);
    _store_data(&&pr_over);
    _store_data(&&pr_count);
    _store_data(&&pr_to_number);

    /*              0= if                                */
    _store_data(&&pr_zero_eq);
    _compile_if();

    /*                  drop nip state @ if literal then */
    _store_data(&&pr_drop);
    _store_data(&&pr_nip);
    _store_data(&&pr_state);
    _store_data(&&pr_fetch);
    _compile_if();
    _store_data(&&pr_literal);
    _compile_then();

    /*              else                                 */
    _compile_else();

    /*                   abort                           */
    _store_data(&&pr_abort);

    /*              then                                 */
    _compile_then();

    /*          then                                     */
    _compile_then();

    /*      repeat                                       */
    _compile_repeat();

    /*  ;                                                */
    _store_data(&&op_exit);

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
