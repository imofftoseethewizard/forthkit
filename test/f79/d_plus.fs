t{  0  0  5  0 d+ ->  5  0 }t
t{ -5 -1  0  0 d+ -> -5 -1 }t
t{  1  0  2  0 d+ ->  3  0 }t
t{  1  0 -1 -1 d+ ->  0  0 }t
t{ -1 -1  2  0 d+ ->  1  0 }t
t{ -1 -1 -2 -1 d+ -> -3 -1 }t
t{ -1 -1  1  0 d+ ->  0  0 }t
t{  0  0  0  5 d+ ->  0  5 }t
t{ -1  5  0  0 d+ -> -1  5 }t
t{  0  0  0 -5 d+ ->  0 -5 }t
t{  0 -5 -1  0 d+ -> -1 -5 }t
t{  0  1  0  2 d+ ->  0  3 }t
t{ -1  1  0 -2 d+ -> -1 -1 }t
t{  0 -1  0  2 d+ ->  0  1 }t
t{  0 -1 -1 -2 d+ -> -1 -3 }t
t{ -1 -1  0  1 d+ -> -1  0 }t

t{ min-int  0 min-int 0 d+ -> 0 1 }t
t{ min-int -1 min-int 0 d+ -> 0 0 }t

t{  hi-2int     1  0 d+ -> 0 hi-int 1+ }t
t{  hi-2int  hi-2int d+ -> 1s 1- max-int }t
t{ max-2int min-2int d+ -> -1 -1 }t
t{ max-2int  lo-2int d+ -> hi-2int }t
t{  lo-2int  lo-2int d+ -> min-2int }t
t{  hi-2int min-2int d+ 1 0 d+ -> lo-2int }t
