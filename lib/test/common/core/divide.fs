: t/ 1 swap */mod swap drop ;

t{       0       1 / ->       0       1 t/ }t
t{       1       1 / ->       1       1 t/ }t
t{       2       1 / ->       2       1 t/ }t
t{      -1       1 / ->      -1       1 t/ }t
t{      -2       1 / ->      -2       1 t/ }t
t{       0      -1 / ->       0      -1 t/ }t
t{       1      -1 / ->       1      -1 t/ }t
t{       2      -1 / ->       2      -1 t/ }t
t{      -1      -1 / ->      -1      -1 t/ }t
t{      -2      -1 / ->      -2      -1 t/ }t
t{       2       2 / ->       2       2 t/ }t
t{      -1      -1 / ->      -1      -1 t/ }t
t{      -2      -2 / ->      -2      -2 t/ }t
t{       7       3 / ->       7       3 t/ }t
t{       7      -3 / ->       7      -3 t/ }t
t{      -7       3 / ->      -7       3 t/ }t
t{      -7      -3 / ->      -7      -3 t/ }t
t{ max-int       1 / -> max-int       1 t/ }t
t{ min-int       1 / -> min-int       1 t/ }t
t{ max-int max-int / -> max-int max-int t/ }t
t{ min-int min-int / -> min-int min-int t/ }t
