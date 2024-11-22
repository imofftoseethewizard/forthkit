: factive? ( n -- f )
    0 f@ =
;

: ffree? ( n -- f )
    fip @ 0=
;

: fpaused? ( n -- f )
    dup fsteps @ 0= swap fip @ 0= 0= and
;

: fscheduled? ( n -- f )
    #f 1
    do
        dup i f@ =
        if
            drop i
            leave
            exit
        then
    loop
    0
;

: run ( n -- )
    -1 over fsteps !
    start
;

: tactive? ( n -- f )
    0 f@ ftask@ =
;

: tfree? ( n -- f )
    tdp @ 0=
;

: tprimary?
    0=
;

: twist ( -- )
    0 braid
;