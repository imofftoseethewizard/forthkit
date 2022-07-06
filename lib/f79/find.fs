: FIND ( -- addr )

    ( Leave the compilation address of the next word name, which is )
    ( accepted from the input stream. If that word cannot be found  )
    ( in the dictionary after a search of CONTEXT and FORTH leave   )
    ( zero.                                                         )

    32 WORD FIND ( FIND here is the built-in FORTH-83 version )
    0=
    IF
        DROP
        0
    THEN
;
