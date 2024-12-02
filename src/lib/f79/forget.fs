: FORGET ( "name" -- )

    \ Used in the form:
    \
    \     FORGET <name>
    \
    \ Delete from the dictionary <name> and all words added to
    \ the dictionary after <name> regardless of the vocabulary.
    \ Failure to find <name> is an error condition.

    \ Parse "name" and leave xt on the stack.
    \ FORTH-79: tick is immediate prior to FORTH-83, so we have
    \ to do this little dance to compile it.
    [ ' ' COMPILE, ]

    \ Calculate the address of the beginning of the word header.
    wa_word_xt -

    \ The name of the word is stored immediately below the word
    \ header in the dictionary. Update the dictionary pointer to
    \ that address.
    DUP wa_word_name + @
    HERE - ALLOT

    \ Update the current vocabulary to point to the word
    \ immediately preceding the forgotten word.
    wa_word_link + @
    CURRENT @ !
;
