ea_pad_buffer_size @ DUP reserve + CONSTANT number_pad0
VARIABLE number_pad

: <#
    number_pad0 number_pad !
;

: #>
    DROP DROP
    number_pad @
    number_pad0 OVER -
;

: HOLD
    number_pad @ 1-
    DUP number_pad !
    C!
;

: compile-digits
    [CHAR] 9 1+ [CHAR] 0 DO I C, LOOP
    [CHAR] Z 1+ [CHAR] A DO I C, LOOP
    [CHAR] z 1+ [CHAR] a DO I C, LOOP
;

CREATE digits compile-digits

: #
    BASE @ ud/mod ROT
    digits + C@ HOLD
;

: #S ( ud -- 0 0 )

    ( ud is converted appending each resultant character into the   )
    ( pictured numeric output string until the quotient -- see # -- )
    ( is zero.  A single zero is added to the output string if the  )
    ( number was initially zero. Typically used between <# and      )
    ( #> .                                                          )

    #
    BEGIN
        OVER OVER OR
    WHILE
            #
    REPEAT
;

: SIGN ( n -- )

    ( If n is negative, an ASCII "-" is appended to the pictured )
    ( numeric output string.  Typically used between <# and #> . )

    (    0< IF [CHAR] - HOLD THEN )
    0< IF [CHAR] - HOLD THEN
;

: U. ( u -- )

    ( "u-dot"                                                      )
    ( Display u converted according to BASE in a free field format )
    ( with one trailing blank.                                     )

    0 <# #S #> TYPE SPACE
;

: . ( n -- )

    ( .  "dot"                                                      )
    (                                                               )
    ( Display n converted according to BASE in a free field format  )
    ( with one trailing blank and with a leading minus sign if n is )
    ( negative.                                                     )


    DUP 0< IF [CHAR] - EMIT THEN
    ABS U.
;
