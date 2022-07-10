: FLUSH
    SAVE-BUFFERS

    ea_buffer_map @
    ea_buffer_count @ CELLS
    OVER + SWAP
    DO
        -1 I !
        CELL
    +LOOP
;
