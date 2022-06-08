: gp2
    <# -1 sign 0 sign -1 sign 0 0 #>
    2 = swap
    dup c@ 45 = swap
    1+ c@ 45 =
    and and ;

t{ gp2 -> <true> }t
