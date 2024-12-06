/*|

The following is a minimal text interpreter using word and find.  It
doesn't have any error reporting, and it only understands words in the
dictionary and unsigned integer literals.

    : interpret
        begin
            \ Read the next space-delimited word from the input stream.
            32 word ?dup
            ( 0 | c-addr c-addr )

        while

            \ Look up the word in the current context. If found, return
            \ its xt and 1 if the word is immediate, -1 otherwise. If the
            \ word is not found, leave the c-addr and push 0.

            find dup
            ( c-addr 0 0 | xt -1 -1 | xt 1 1 )
            if
                0> state @ 0= or
                if execute else compile, then

            else
                \ The word was not found in the current context. Attempt to
                \ interpret it as a literal.

                ( c-addr 0 )
                over count >number
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
  |*/

// INTERPRET

cw_interpret:
{
    // Save code address for use by evaluate.
    _set_interpret(_from_ptr(dp));

    _compile_begin();

    _compile_literal(32);
    _compile_literal(_from_ptr(&e[ea_word_buffer0]));
    _compile_pw(pr_fetch);
    _compile_pw(pr_word);
    _compile_pw(pr_query_dup);

    _compile_while();

    _compile_pw(pr_find);
    _compile_pw(pr_dup);

    _compile_if();

    _compile_pw(pr_zero_gt);
    _compile_pw(pr_state);
    _compile_pw(pr_fetch);
    _compile_pw(pr_zero_eq);
    _compile_pw(pr_or);

    _compile_if();
    _compile_pw(pr_execute);
    _compile_else();
    _compile_pw(pr_store_compiled);
    _compile_then();

    _compile_else();

    _compile_pw(pr_over);
    _compile_pw(pr_count);
    _compile_pw(pr_to_number);

    _compile_pw(pr_zero_eq);
    _compile_if();

    _compile_pw(pr_drop);
    _compile_pw(pr_swap);
    _compile_pw(pr_drop);
    _compile_pw(pr_state);
    _compile_pw(pr_fetch);
    _compile_if();
    _compile_pw(pr_literal);
    _compile_then();

    _compile_else();

    _compile_literal(err_undefined_word);
    _compile_pw(op_abort);

    _compile_then();

    _compile_then();

    _compile_repeat();
}
