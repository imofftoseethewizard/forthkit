: [']
    32 WORD
    ?DUP
    IF
        FIND
        ?DUP
        IF
            COMPILE,
        ELSE
            err_unrecognized_word <abort>
        THEN
    ELSE
        ABORT
    THEN

; IMMEDIATE