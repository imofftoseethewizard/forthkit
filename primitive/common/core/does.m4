__primitive(pr_do_does)
{
    register cell *word = _to_ptr(*_to_ptr(tp[ta_current]));
    register cell *origp = _get_word_interpretation_ptr(word);

    *origp = (cell)_from_pr(op_does);
    *(origp + 1) = *sp++;

}
__end
__define_primitive("<do-does>", pr_do_does);

__primitive(pr_does)
{
    /* DOES> ( -- addr ) compiling: ( -- ) "does"

       Defines the execution-time action of a word created by a
       high-level defining word.  Used in the form:

       |   : <namex> ... <create> ... DOES> ... ;

       and then

       |   <namex> <name>

       where <create> is CREATE or any user defined word which
       executes CREATE .

       Marks the termination of the defining part of the defining
       word <namex> and then begins the definition of the
       execution-time action for words that will later be defined
       by <namex>.  When <name> is later executed, the address of
       <name>'s parameter field is placed on the stack and then the
       sequence of words between DOES> and ; are executed.

       At compile time, does> must capture the location of the code
       that follows does>. Keeping in mind that the compile-time
       context of does> is that we are compiling a new compiling
       word, and the address of the code after does> will be
       compiled into the new words defined with the word now being
       defined. The compile-time result should be to compile
       op_do_does

       At interpretation time, do_does> runs during the creation of
       a new word.  As left by does> at compile time, the location
       of the does> code is on the stack and the word being defined
       is available in tp[ta_current].  (See preamble.h "Add to
       current vocabulary.") Assuming it was created with CREATE,
       the body of the word will so far be

       |   op_literal
       |   <addr of cell below op_exit>
       |   op_exit

       to implement DOES>, this could either be replaced with

       |   op_does
       |   <offset to does> code>
       |   op_exit

       where op_does presumes that the parameter address
       immediately follows an exit.

       |   op_literal
       |   <addr of cell below op_exit>
       |   <does code>

       The first may be slightly faster to execute, since there
       will be one less indirection and one less exit, ultimately,
       but it is a little more delicate to code. The first has the
       other advantage of being inherently relocatable for
       reloading images. Despite it being finicky to implement, it
       seems the better approach.
     */

    _compile_pr(op_literal);
    _store_data(_from_ptr((cell *)dp + 3));
    _compile_pr(pr_do_does);
    _compile_pr(op_exit);

    _check_dictionary_bounds();
}
__end
__define_immediate_primitive("DOES>", pr_does);
