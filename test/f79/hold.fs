: gp1
    <# 41 hold 42 hold 0 0 #>
    2 = swap
    dup c@ 42 = swap
    1+ c@ 41 =
    and and ;

t{ gp1 -> <true> }t
