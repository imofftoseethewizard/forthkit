: POSTPONE
    BL WORD FIND
    ?DUP
    IF
        0<
        IF
            ['] <literal> COMPILE,
            ,
            ['] COMPILE,
        THEN
        COMPILE,
    ELSE
        err_undefined_word <abort>
    THEN
; IMMEDIATE
