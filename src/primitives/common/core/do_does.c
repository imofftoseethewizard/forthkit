/*|

  `pr_do_does` provides the execution semantics of `DOES>`.  This is
  the second primitive in a set of three which implement `DOES>`.  The
  first `pr_does` provides the compilation semantics and compiles this
  primitive into the defining word.  `pr_do_does` executes during that
  defining word, adjusting the word being defined so that it
  implements the execution semantics that follows `DOES>` in the
  definition of the defining word.  It is presumed that the new word
  was defined with `CREATE`, and the code below is only guaranteed to
  be correct under that assumption.

  Here, `_current` points to the word being defined (by the defining
  word containing `DOES>`).  We use this to find the start of the code
  implementing the execution semantics of the new word and replace the
  original semantics with `op_does`, the third primitive which
  implements `DOES>`, providing the execution semantics of the words
  defined with the defining word which contains `DOES>`.

  |*/

pr_do_does:
{
    register cell *word = _to_ptr(*_to_ptr(_current()));
    register cell *origp = _get_word_interpretation_ptr(word);

    *origp = (cell)_from_pr(op_does);
    *(origp + 1) = *sp++;
}
