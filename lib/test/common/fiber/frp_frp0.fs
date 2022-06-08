( check that initially, rp is one cell below rp0 )
t{ ' dup fiber dup frp0 @ over frp @ - swap start -> cell cell }t

( check that initially, rp points to 0 )
t{ ' dup fiber dup frp @ @ swap start -> 0 0 }t

( check that the fiber's return stack is empty after the fiber finishes )
t{ ' dup fiber dup start frp @ swap frp0 @ = -> <true> }t