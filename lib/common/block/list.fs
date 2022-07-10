: LIST
    DUP SCR !
    BLOCK
    DUP ea_buffer_size @ + SWAP
    DO
        I @ EMIT
    LOOP
;
