_primitive(pr_does) {
    /* The word being defined will be available in e[ea_current].
       (See preamble.h "Add to current vocabulary.") Assuming it was
       created with CREATE, the body of the word will so far be

           op_literal
           <addr of cell below op_exit>
           op_exit

       to implement DOES>, this could either be replaced with

           op_jump
           <offset to here>
           op_exit

       or

           <address of here>
           op_exit
           op_exit

       where op_exit in the third position is never hit, and where
       here has

           op_literal
           <addr of cell below op_exit>
           <does code>

       The first may be slightly faster to execute, since there will
       be one less indirection and one less exit, ultimately, but it
       is a little more delicate to code. The first has the other
       advantage of being inherently relocatable for reloading
       images. Despite it being finicky to implement, it seems the
       better approach.
    */
    register cell *word = _to_ptr(e[ea_current]);
    register cell *origp = _get_word_interpretation_ptr(word);
    register cell *doesp = (cell *)here;

    _store_data(*origp);
    _store_data(*(origp+1));

    *origp = (cell)_pr_addr(op_jump);
    *(origp+1) = doesp - origp + sizeof(cell);

    _next();
}
_define_primitive("DOES>", pr_does);
