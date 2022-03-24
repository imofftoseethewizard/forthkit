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
