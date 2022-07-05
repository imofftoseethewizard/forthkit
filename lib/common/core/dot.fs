: . ( n -- )

(       .  "dot"                                                      )
(                                                                     )
(       Display n converted according to BASE in a free field format  )
(       with one trailing blank and with a leading minus sign if n is )
(       negative.                                                     )


    dup 0< if 45 emit then
    abs u.
;
