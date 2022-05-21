        /*
         * The following is a minimal text interpreter using word and find.
         * It doesn't have any error reporting, and it only understands words
         * in the dictionary and unsigned integer literals.
         *
         * : interpret
         *     begin
         *         \ Read the next space-delimited word from the input stream.
         *         32 word ?dup
         *         ( 0 | c-addr c-addr )
         *
         *     while
         *
         *         \ Look up the word in the current context. If found, return
         *         \ its xt and 1 if the word is immediate, -1 otherwise. If the
         *         \ word is not found, leave the c-addr and push 0.
         *
         *         dup find ?dup
         *         ( c-addr 0 | c-addr xt xt )
         *         if
         *             ( c-addr xt )
         *
         *             swap drop
         *
         *             \ Check state and the immediate flag, executing or compiling
         *             \ as appropriate. The flags of the word is in the cell immediately
         *             \ before the compilation address, and the immediate flag is
         *             \ in the lsb.
         *
         *             dup <cell> - @ 1 and state @ 0= or
         *             if execute else compile, then
         *
         *         else
         *             \ The word was not found in the current context. Attempt to
         *             \ interpret it as a literal.
         *
         *             ( c-addr )
         *             0 over count >number
         *             ( c-addr ud c-addr2 u )
         *
         *             \ If u is 0, then the entirety of the word was consumed in converting
         *             \ it to a number, and that will be in ud.
         *
         *             0= if
         *
         *                 \ c-addr and c-addr2 aren't needed anymore, so drop, swap, and drop
         *                 \ clear them out. If we're compiling, then compile a literal,
         *                 \ else just leave the value on the stack.
         *
         *                 drop swap drop state @ if literal then
         *             else
         *
         *                 \ <abort> refers to the internal operator for abort, which is much like
         *                 \ throw in later FORTH versions. -13 is the throw code for an
         *                 \ unrecognized word. See https://forth-standard.org/standard/exception
         *
         *                 -13 <abort>
         *             then
         *         then
         *     repeat
         * ;
         *
         * It's compiled line by line below.
         */

_begin_define_word("interpret", 0);
e[ea_interpret] = _from_ptr(dp);

_compile_begin();

_compile_literal(32);
_compile_literal(_from_ptr(&e[ea_word_buffer0]));
_compile_pr(pr_fetch);
_compile_pr(pr_word);
_compile_pr(pr_q_dup);

_compile_while();

_compile_pr(pr_dup);
_compile_pr(pr_find);
_compile_pr(pr_q_dup);

_compile_if();

_compile_pr(pr_swap);
_compile_pr(pr_drop);

_compile_pr(pr_dup);
_compile_literal(sizeof(cell));
_compile_pr(pr_minus);
_compile_pr(pr_fetch);
_compile_literal(1);
_compile_pr(pr_and);
_compile_pr(pr_state);
_compile_pr(pr_fetch);
_compile_pr(pr_zero_eq);
_compile_pr(pr_or);

_compile_if();
_compile_pr(pr_execute);
_compile_else();
_compile_pr(pr_store_compiled);
_compile_then();

_compile_else();

_compile_literal(0);
_compile_pr(pr_over);
_compile_pr(pr_count);
_compile_pr(pr_to_number);

_compile_pr(pr_zero_eq);
_compile_if();

_compile_pr(pr_drop);
_compile_pr(pr_swap);
_compile_pr(pr_drop);
_compile_pr(pr_state);
_compile_pr(pr_fetch);
_compile_if();
_compile_pr(pr_literal);
_compile_then();

_compile_else();

_compile_literal(-13);
_compile_pr(op_abort);

_compile_then();

_compile_then();

_compile_repeat();

_compile_pr(op_exit);

sp = sp0;
rp = rp0;
ip = 0;
