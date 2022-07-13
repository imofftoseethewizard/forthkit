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
