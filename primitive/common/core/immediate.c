primitive pr_immediate()
{
    /* IMMEDIATE ( -- )

       Marks the most recently created dictionary entry as a word
       which will be executed when encountered during compilation
       rather than compiled.
     */

    _set_word_flags(_to_ptr(*_to_ptr(tp[ta_current])), c_immediate);
}
