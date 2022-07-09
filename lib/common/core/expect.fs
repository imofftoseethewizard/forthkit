: EXPECT ( addr +n -- )

    ( Receive characters and store each into memory.  The transfer )
    ( begins at addr proceeding towards higher addresses one byte  )
    ( per character until either a "return" is received or until   )
    ( +n characters have been transferred.  No more than +n        )
    ( characters will be stored.  The "return" is not stored into  )
    ( memory.  No characters are received or transferred if +n is  )
    ( zero.  All characters actually received and stored into      )
    ( memory will be displayed, with the "return" displaying as a  )
    ( space.                                                       )

    DUP SPAN !
    0 DO
        KEY
        DUP 10 =
        IF
            DROP
            I SPAN !
            LEAVE
        ELSE
            OVER I + C!
        THEN
    LOOP
    DROP
;
