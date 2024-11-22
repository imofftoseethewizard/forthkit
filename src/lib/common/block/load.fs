: LOAD ( u -- )

    ( The contents of >IN and BLK, which locate the current input )
    ( stream, are saved. The input stream is then redirected to   )
    ( the beginning of screen u by setting >IN to zero and BLK to )
    ( u. The screen is then interpreted. If interpretation from   )
    ( screen u is not terminated explicitly it will be terminated )
    ( when the input stream is exhausted and then the contents of )
    ( >IN and BLK will be restored. An error condition exists if  )
    ( u is zero.                                                  )

    DUP 0= IF err_invalid_block_number <abort> THEN

    ( Save current input state. )
    TIB @ >R
    #TIB @ >R
    >IN @ >R
    BLK @ >R

    ( Load block and set input state for interpret. )
    0 >IN !
    DUP BLK !
    BLOCK TIB !
    ea_buffer_size @ #TIB !

    interpret

    ( Restore input state. )
    R> BLK !
    R> >IN !
    R> #TIB !
    R> TIB !
;