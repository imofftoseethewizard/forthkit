: tmod 1 swap */mod drop ;

t{       0       1 mod ->       0       1 tmod }t
t{       1       1 mod ->       1       1 tmod }t
t{       2       1 mod ->       2       1 tmod }t
t{      -1       1 mod ->      -1       1 tmod }t
t{      -2       1 mod ->      -2       1 tmod }t
t{       0      -1 mod ->       0      -1 tmod }t
t{       1      -1 mod ->       1      -1 tmod }t
t{       2      -1 mod ->       2      -1 tmod }t
t{      -1      -1 mod ->      -1      -1 tmod }t
t{      -2      -1 mod ->      -2      -1 tmod }t
t{       2       2 mod ->       2       2 tmod }t
t{      -1      -1 mod ->      -1      -1 tmod }t
t{      -2      -2 mod ->      -2      -2 tmod }t
t{       7       3 mod ->       7       3 tmod }t
t{       7      -3 mod ->       7      -3 tmod }t
t{      -7       3 mod ->      -7       3 tmod }t
t{      -7      -3 mod ->      -7      -3 tmod }t
t{ max-int       1 mod -> max-int       1 tmod }t
t{ min-int       1 mod -> min-int       1 tmod }t
t{ max-int max-int mod -> max-int max-int tmod }t
t{ min-int min-int mod -> min-int min-int tmod }t
