pr_do_colon:
{
    /* : ( -- sys ) "colon"

       A defining word executed in the form:

       |   : <name> ... ;

       Create a word definition for <name> in the compilation
       vocabulary and set compilation state.  The search order is
       changed so that the first vocabulary in the search order is
       changed so that the first vocabulary in the search order is
       replaced by the compilation vocabulary.  The compilation
       vocabulary is unchanged.  The text from the input stream is
       subsequently compiled.  <name> is called a "colon
       definition".  The newly created word definition for <name>
       cannot be found in the dictionary until the corresponding ;
       or ;CODE is successfully processed.

       An error condition exists if a word is not found and cannot
       be converted to a number or if, during compilation from mass
       storage, the input stream is exhausted before encountering ;
       or ;CODE .  sys is balanced with its corresponding ; .
     */

    _set_context(_current());
    _set_state(1);

    _store_word_name();
    _word_header(0);
}
