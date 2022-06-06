here 0 , here - dup allot negate constant cell

: cell+ cell + ;
: cells cell * ;
: nip swap drop ;

12 constant w.xt
8 constant w.flags
4 constant w.next
2 constant wf-inline
16 constant wf-op-ip-offset
32 constant wf-op-literal

: xt-primitive? 0< ;
: word-flags w.flags + @ ;
: word-xt w.xt + ;
: first-word current @ @ ;
: next-word w.next + @ ;
: inline? word-flags wf-inline and 0= 0= ;
: has-op-literal? word-flags wf-op-literal and 0= 0= ;
: has-op-ip-offset? word-flags wf-op-ip-offset and 0= 0= ;

: find-word ( cond-xt -- w | 0 )
    >r

    first-word
    begin
        dup
    while
            r@ execute
            if
                r> drop exit
            then
            next-word
    repeat
    r> drop
;

: match-primitive? ( xt w -- xt w f )
    dup inline?
    over word-xt @ 4 pick =
    and
;

: match-compiled? ( xt w -- xt w f )
    dup word-xt 3 pick =
;

: xt>word ( xt -- w | 0 )

    dup xt-primitive?
    if ' match-primitive? else ' match-compiled? then
    find-word
    swap drop ( remove xt from below the result )
;

: decompile ( addr n -- )

    0 do
        dup dup .
        @ xt>word
        ?dup
        if
            dup
            @ count type
            dup has-op-literal?
            if
                drop
                space cell+ dup @ .
            else
                has-op-ip-offset?
                if
                    space cell+ dup @ over + cell - .
                then
            then
        else
            ." <unknown>" space dup @ .
        then
        cr
        cell+
    loop
    drop
;
