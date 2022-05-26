: "10"= 2 = swap dup c@ 49 = swap 1+ c@ 48 = and and ;

: gp5
    base @ <true>
    max-base 1+ 2 do
        i base !
        i 0 <# #s #> "10"= and
    loop
    swap base ! ;

t{ gp5 -> <true> }t

: gp6
    base @ >r 2 base !
    max-uint max-uint <# #s #>
    r> base !
    dup #bits-ud = swap
    0 do
        over c@ 49 = and
        >r char+ r>
    loop swap drop ;

t{ gp6 -> <true> }t

: gp7 [ decimal ]
    base @ >r max-base base !
    <true>
    10 0 do
        i 0 <# #s #> 1 = swap c@ i 48 + = and and
    loop
    max-base 10 do
        i 0 <# #s #> 1 = swap c@ 97 i 10 - + = and and
    loop
    r> base ! ;

t{ gp7 -> <true> }t
