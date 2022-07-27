: :NONAME
    HERE           \ nt (address of a counted string)
    0 ,            \ the counted string itself
    HERE           \ address of the new word, ie. colon-sys
    SWAP ,         \ store nt in first word cell
    CURRENT @ @ ,  \ store link address to next word in dictionary
    0 ,            \ word flags
    HERE           \ xt
    SWAP
    ( xt colon-sys )
    1 STATE !
;