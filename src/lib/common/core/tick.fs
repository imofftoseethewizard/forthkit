: ' ( -- addr)

    ( "tick"                                                   )
    (                                                          )
    ( Used in the form:                                        )
    (                                                          )
    ( |  '  <name>                                             )
    (                                                          )
    ( addr is the compilation address of <name>.  An error     )
    ( condition exists if <name> is not found in the currently )
    ( active search order.                                     )

    32 WORD FIND
    0= IF err_undefined_word <abort> THEN
;