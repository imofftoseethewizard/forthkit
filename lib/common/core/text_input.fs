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
        2DUP >
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

: WORD ( char -- addr )

    \ Generates a counted string by non-destructively accepting
    \ characters from the input stream until the delimiting
    \ character char is encountered or the input stream is
    \ exhausted.  Leading delimiters are ignored.  The entire
    \ character string is stored in memory beginning at addr as a
    \ sequence of bytes.  The string is followed by a blank which
    \ is not included in the count.  The first byte of the string
    \ is the number of characters {0..255}.  If the string is
    \ longer than 255 characters, the count is unspecified.  If
    \ the input stream is already exhausted as WORD is called,
    \ then a zero length character string will result.
    \
    \ If the delimiter is not found the value of >IN is the size
    \ of the input stream.  If the delimiter is found >IN is
    \ adjusted to indicate the offset to the character following
    \ the delimiter.  #TIB is unmodified.
    \
    \ The counted string returned by WORD may reside in the "free"
    \ dictionary area at HERE or above.  Note that the text
    \ interpreter may also use this area.  See:  "input stream"

    ea_word_buffer1 @ <word>
;
