t{ 0 0 u* -> 0 0 }t
t{ 0 1 u* -> 0 0 }t
t{ 1 0 u* -> 0 0 }t
t{ 1 2 u* -> 2 0 }t
t{ 2 1 u* -> 2 0 }t
t{ 3 3 u* -> 9 0 }t

t{ mid-uint+1 1 rshift 2 u* ->  mid-uint+1 0 }t
t{ mid-uint+1          2 u* ->           0 1 }t
t{ mid-uint+1          4 u* ->           0 2 }t
t{         1s          2 u* -> 1s 1 lshift 1 }t
t{   max-uint   max-uint u* ->    1 1 invert }t
