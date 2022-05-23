(  ---------------------------------------------------------  )
(  Supplemental Words                                         )
(                                                             )
(  FORTH-79 doesn't have the words "cell" or "cells", since   )
(  since the cell size was defined to be 16 bits. Forthkit    )
(  supports compiling f79 with 16, 32, or 64 bit words.       )

here 0 , here - dup allot negate constant cell

: cell+ cell + ;
: cells cell * ;
: char+ 1+ ;
: chars ;
: <> = 0= ; : invert not ;

(  ---------------------------------------------------------  )
(  Test Harness Variables                                     )
(                                                             )
(  The test harness captures the depth of the stack before    )
(  the test is run. After the subject code is executed, the   )
(  depth of the stack is checked against this and any new     )
( values are saved for comparison during verification.        )

variable start-depth
variable actual-depth

create actual-results 32 cells allot

: t{ depth start-depth ! ;

: ->
    depth dup actual-depth !
    start-depth @ >
    if
        depth start-depth @ - 0
        do
            actual-results i cells + !
        loop
    then
;

: dot 46 emit ;

: }t

    depth actual-depth @ <>
    if
        ." wrong number of results."
        abort
    then

    depth start-depth @ >
    if
        depth start-depth @ - 0
        do
            actual-results i cells + @ <>
            if
                ." incorrect result"
                abort
            then
        loop
    then
    dot

    depth start-depth @ >
    if
        depth start-depth @ do drop loop
    then
;

(  ---------------------------------------------------------  )
(  Constants                                                  )

0      0= constant <true>
<true> 0= constant <false>

0         constant 0s
-1        constant 1s

decimal 36 constant max-base

: count-bits
    0 0 not begin dup while >r 1+ r> 2 * repeat drop ;

count-bits 2 * constant #bits-ud

0 invert                 constant max-uint
0 invert 1 rshift        constant max-int
0 invert 1 rshift invert constant min-int
0 invert 1 rshift        constant mid-uint
0 invert 1 rshift invert constant mid-uint+1
max-int 2 /              constant hi-int
min-int 2 /              constant lo-int

: max-2int 1s max-int ;
: min-2int 0s min-int ;
: hi-2int 1s hi-int ;
: lo-2int 0s lo-int ;
