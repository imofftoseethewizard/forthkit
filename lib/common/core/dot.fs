: . ( n -- )

(       .  "dot"                                                      )
(                                                                     )
(       Display n converted according to BASE in a free field format  )
(       with one trailing blank and with a leading minus sign if n is )
(       negative.                                                     )


    DUP 0< IF 45 EMIT THEN
    ABS U.
;
