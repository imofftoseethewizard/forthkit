: CHAR ( "<spaces>name" -- char )

    \ Skip leading space delimiters. Parse name delimited by a
    \ space. Put the value of its first character onto the stack.

    BL WORD COUNT DROP C@
;