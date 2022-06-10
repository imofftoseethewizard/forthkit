: t/mod over over / >r mod r> ;

t{       0       1 /mod ->       0       1 t/mod }t
t{       1       1 /mod ->       1       1 t/mod }t
t{       2       1 /mod ->       2       1 t/mod }t
t{      -1       1 /mod ->      -1       1 t/mod }t
t{      -2       1 /mod ->      -2       1 t/mod }t
t{       0      -1 /mod ->       0      -1 t/mod }t
t{       1      -1 /mod ->       1      -1 t/mod }t
t{       2      -1 /mod ->       2      -1 t/mod }t
t{      -1      -1 /mod ->      -1      -1 t/mod }t
t{      -2      -1 /mod ->      -2      -1 t/mod }t
t{       2       2 /mod ->       2       2 t/mod }t
t{      -1      -1 /mod ->      -1      -1 t/mod }t
t{      -2      -2 /mod ->      -2      -2 t/mod }t
t{       7       3 /mod ->       7       3 t/mod }t
t{       7      -3 /mod ->       7      -3 t/mod }t
t{      -7       3 /mod ->      -7       3 t/mod }t
t{      -7      -3 /mod ->      -7      -3 t/mod }t
t{ max-int       1 /mod ->       0 max-int       }t
t{ min-int       1 /mod ->       0 min-int       }t
t{ max-int max-int /mod ->       0       1       }t
t{ min-int min-int /mod ->       0       1       }t
