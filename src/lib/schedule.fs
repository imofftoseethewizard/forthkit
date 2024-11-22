variable steps

10 steps !

( Each fiber should have its own task -- i.e. its own parameter stack --       )
( since the point at which a fiber may stop is unpredictable, and any use of   )
( the parameter stack would otherwise cause unwanted crosstalk between fibers. )

: round-robin
    begin
        #f 1-
    while
            1
            begin
                dup #f <
            while
                    dup braid
                    1 f@
                    steps @ over fsteps !
                    twist
                    dup fip @ 0=
                    if
                        drop
                    else
                        lay
                        1+
                    then
            repeat
            drop
    repeat
;

( example )

: reserve-task dup reserve swap task ;

10 reserve-task constant comma-task
10 reserve-task constant cr-task
10 reserve-task constant star-task

variable comma-count
100 comma-count !

variable star-count
100 star-count !

variable cr-count
16 cr-count !

: commas comma-count @ 0 do 44 emit loop ;
: crs cr-count @ 0 do 10 0 do loop cr loop ;
: stars star-count @ 0 do 42 emit loop ;

: comma-fiber ' commas fiber dup comma-task over ftask ! ;
: cr-fiber ' crs fiber dup cr-task over ftask ! ;
: star-fiber ' stars fiber dup star-task over ftask ! ;

: demo-round-robin
    comma-fiber lay
    cr-fiber lay
    star-fiber lay
    round-robin
;