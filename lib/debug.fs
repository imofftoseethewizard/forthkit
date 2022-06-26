1000 constant dbg-dict-size
dbg-dict-size reserve constant dbg-dict-start

dbg-dict-size dbg-dict-start task constant dbg-task

variable dbg-fiber
-1 dbg-fiber !

: debug ( xt -- )
    fiber
    dbg-task over ftask !
    dbg-fiber !
;

: \.r
    base @ >r
    decimal 16 base !

    dbg-fiber @ >r

    ." ip: "   r@ fip     @         u.
    ." *ip: "  r@ fip     @ @       u.
    ." stop: " r@ fstop   @         u.
    ." rp: "   r@ frp     @         u.
    ." *rp: "  r@ frp     @ @       u.
    ." sp: "   r@ ftask   @ tsp @   u.
    ." *sp: "  r@ ftask   @ tsp @ @ u.
    ." dp: "   r@ ftask   @ tdp @   u.

    cr

    r> drop
    r> base !
;

: \m ( n -- )
    dbg-fiber @ fsteps !
    dbg-fiber @ start
;

: \r
    dbg-fiber @ frp0 @ dbg-fiber @ fstop !
    -1 \m
;

: \o
    dbg-fiber @ frp @ cell+ dbg-fiber @ fstop !
    -1 \m
;

: \s 1 \m ;

: \n
    dbg-fiber @ >r

    r@ fip @ @
    primitive?
    if
        \s
    else
        r@ frp @ r@ fstop !
        -1 \m
    then

    r> drop
;
