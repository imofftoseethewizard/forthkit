base @
decimal

0 cells constant w.nt
1 cells constant w.next
2 cells constant w.flags
3 cells constant w.xt

2 base !

00000001 constant wf-immediate
00000010 constant wf-inline
00000100 constant wf-primitive
00001000 constant wf-value
00010000 constant wf-op-ip-absolute
00100000 constant wf-op-ip-offset
01000000 constant wf-op-indirect-ip-offset
10000000 constant wf-op-literal

base !

: word-flags w.flags + @ ;
: word-xt w.xt + ;
: first-word current @ @ ;
: next-word w.next + @ ;

: inline-word? word-flags wf-inline and 0= 0= ;
: primitive-word? word-flags wf-primitive and 0= 0= ;
: has-op-literal? word-flags wf-op-literal and 0= 0= ;
: has-op-ip-absolute? word-flags wf-op-ip-absolute and 0= 0= ;
: has-op-ip-offset? word-flags wf-op-ip-offset and 0= 0= ;
: has-op-indirect-ip-offset? word-flags wf-op-indirect-ip-offset and 0= 0= ;

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
    dup primitive-word?
    over inline-word? and
    over word-xt @ 4 pick =
    and
;

: match-compiled? ( xt w -- xt w f )
    dup word-xt 3 pick =
;

: xt>word ( xt -- w | 0 )

    dup primitive?
    if [ ' match-primitive? ] literal else [ ' match-compiled? ] literal then
    find-word
    swap drop ( remove xt from below the result )
;

: decompile ( addr n -- )

    0 do
        dup dup .
        @ xt>word
        ?dup
        if
            ( display word name )
            dup @ count type

            ( display word operands )
            dup has-op-literal?
            over has-op-ip-absolute? or
            if
                drop
                space cell+ dup @ .
            else
                has-op-ip-offset?
                if
                    space cell+ dup @ over + .
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
