ea_source_addr CONSTANT TIB
ea_source_idx  CONSTANT >IN
ea_source_len  CONSTANT #TIB

: \
    #TIB @ >IN !
; IMMEDIATE

: ( \ ( "ccc<paren>" -- )

    \ Parse ccc delimited by ) (right parenthesis). ( is an
    \ immediate word. The number of characters in ccc may be zero
    \ to the number of characters in the parse area.

    TIB @ #TIB @ OVER + SWAP >IN @ +
    \ The stack now contains the address beyond the last character
    \ in the text input buffer below the address of the next
    \ character in the buffer.

    BEGIN
        \ ( c-addr-last c-addr-current )
        2dup >
    WHILE
            \ `41` is used here instead of `[CHAR] )` to minimize
            \ the amount of code before comments are fully
            \ supported.
            DUP C@ 41 <>
        WHILE
                1+
        REPEAT

        \ Execution continues here when a closing paren is found.
        \ Set >IN to the index of the next character beyond that.
        TIB @ - 1+
        >IN !
        DROP

    ELSE
        \ Execution continues here when the closing paren is not
        \ found. Consume the rest of the buffer.
        2DROP
        #TIB @ >IN !

    THEN

; IMMEDIATE
